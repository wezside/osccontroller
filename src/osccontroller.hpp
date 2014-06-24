#ifndef __OSCCONTROLLER_HPP__
#define __OSCCONTROLLER_HPP__

#include <fstream>

#include "ofxOsc.h"
#include "jsonxx.h"
#include "abletontrackinfo.hpp"

#define HOST "192.168.0.227"
#define PORT_SEND 9000
#define PORT_RECEIVE 9001

namespace wezside
{
	class OSCController
	{
	private:
		bool beat;
		jsonxx::Object mapping;
		jsonxx::Array trackArr;
		ofxOscSender osc_sender;
		ofxOscReceiver osc_receiver;

		std::vector<std::string> groups;
		std::vector<wezside::AbletonTrackInfo> info;

		int trackIndexForGroup(int index)
		{
			int lookup_index = 0;
			for (unsigned int i = 0; i < trackArr.size(); ++i)
			{
				if (trackArr.get<jsonxx::Object>(i).has<jsonxx::Boolean>("group"))
				{
					if (index == lookup_index)
					{
						lookup_index = i;
						break;	
					} 
					lookup_index++;
				}
			}
			return lookup_index;
		}

	public:
		OSCController() {}
		OSCController(const OSCController& s) {}
		OSCController& operator=(OSCController& s){return s;}
		~OSCController() {}

		void init()
		{
			osc_sender.setup(HOST, PORT_SEND);
			osc_receiver.setup(PORT_RECEIVE);	
		}	
		void load(std::string json)
		{
			std::ifstream infile(json.c_str());
			std::string line;
			std::string content;
			while (std::getline(infile, line))
			{
				content += line;
			}
			infile.close();
			mapping.parse(content);
			trackArr = mapping.get<jsonxx::Array>("data");
		}
		void save()
		{
			
		}
		virtual void start()
		{
			ofxOscMessage m;
			m.setAddress("/live/play");
			osc_sender.sendMessage(m);
		}
		virtual void stop()
		{
			ofxOscMessage m;
			m.setAddress("/live/stop");
			osc_sender.sendMessage(m);
		}
		virtual void listen()
		{
			while(osc_receiver.hasWaitingMessages())
			{
				ofxOscMessage m;
				osc_receiver.getNextMessage(&m);
				if (m.getAddress() == "/live/play")
				{
				}
				if (m.getAddress() == "/live/tracks")
				{
					int scene = m.getArgAsInt32(0);
					ofLog(OF_LOG_NOTICE, "%s %d", "Total Tracks #", scene);
				}
				if (m.getAddress() == "/live/name/track")
				{
					int track = m.getArgAsInt32(0);
					std::string track_name = m.getArgAsString(1);

					trackArr << jsonxx::Object("track_name", track_name);
					for (unsigned int i = 0; i < groups.size(); ++i)
					{
						if (groups.at(i) == track_name)
						{
							trackArr.get<jsonxx::Object>(track) << "group" << true;
						}
					}
					mapping << "data" << trackArr;
					info.push_back(wezside::AbletonTrackInfo(track_name, track));
				}
				if (m.getAddress() == "/live/beat")
				{
					beat = true;
				}					
				if (m.getAddress() == "/live/volume")
				{
					unsigned int track = m.getArgAsInt32(0);
					float track_volume = m.getArgAsFloat(1);
					ofLog(OF_LOG_NOTICE, "Track Volume %d [%f]", track, track_volume);
					if (track < info.size())
					{
						info.at(track).setVolume(track_volume);
					}
					else ofLog(OF_LOG_WARNING, "There was a problem storing the track #%d volume value of %f", track, track_volume);
				}
			}
		}
		void getInfo(std::vector<wezside::AbletonTrackInfo>& track_info)
		{
			track_info = info;
		}
		bool getBeat()
		{
			return beat;
		}
		void setBeat(bool val)
		{
			beat = val;
		}
		void liveOSCAPI(std::string address, int valint = -1, float valfloat = -99999.0f)
		{
			ofxOscMessage m;
			m.setAddress(address);
			if (valint != -1) m.addIntArg(valint);
			if (valfloat != -99999.0f) m.addIntArg(valfloat);
			osc_sender.sendMessage(m);
		}
		/**
		 * Set a track volume. 
		 * @param track  Track Index - if groups are used within Ableton then the group will form part of the overall track index. 
		 * @param volume Clamped float value for volume in range 0.0 to 1.0
		 */
		void setTrackVolume(int track, float volume)
		{
			ofxOscMessage m;
			m.setAddress("/live/volume");
			m.addIntArg(track);
			m.addFloatArg(ofClamp(volume, 0.0f, 1.0f));
			osc_sender.sendMessage(m);
		}
		/**
		 * Set a track volume by track name. 
		 * @param track  Track Index - if groups are used within Ableton then the group will form part of the overall track index. 
		 * @param volume Clamped float value for volume in range 0.0 to 1.0
		 */
		void setTrackVolume(std::string track_name, float volume)
		{
			for (unsigned int i = 0; i < trackArr.size(); ++i)
			{
				if (trackArr.get<jsonxx::Object>(i).get<jsonxx::String>("track_name") == track_name)
				{
					ofxOscMessage m;
					m.setAddress("/live/volume");
					m.addIntArg(i);
					m.addFloatArg(ofClamp(volume, 0.0f, 1.0f));
					osc_sender.sendMessage(m);
					break;
				}
			}
		}		
		void getTrackVolume(int track)
		{
			ofxOscMessage m;
			m.setAddress("/live/volume");
			m.addIntArg(track);
			osc_sender.sendMessage(m);
		}
		void getGroupVolume(int group_index)
		{
			int track_index = trackIndexForGroup(group_index);
			getTrackVolume(track_index);
		}
		/**
		 * Sets the group volume. Only use if an ableton JSON mapping file is used. Also this will only work if the 
		 * groups aren't collapsed in Ableton. If all the tracks are visible for all the groups then use this function. Reason is
		 * track index will be only used for visible tracks in Ableton. If all your groups are collapsed rather just use setTrackVolume.
		 * @param index Group Index
		 * @param volume Float value for volume in range 0.0 to 1.0
		 * @param group_tracks If true will set all the tracks within a group's volume
		 * @param exclude_group If true excludes the group track itself from volume adjustment
		 */
		void setGroupVolume(int index, float volume, bool group_tracks = false, bool exclude_group = false)
		{
			int lookup_index = trackIndexForGroup(index);
			if (!exclude_group)
			{
				ofxOscMessage m;
				m.setAddress("/live/volume");
				m.addIntArg(lookup_index);
				m.addFloatArg(ofClamp(volume, 0.0f, 1.0f));
				osc_sender.sendMessage(m);
			}

			if (!group_tracks) return;

			// Set the volume of all the tracks associated with the group
			for (unsigned int i = lookup_index+1; i < trackArr.size(); ++i)
			{
				if (trackArr.get<jsonxx::Object>(i).has<jsonxx::Boolean>("group"))
				{
					break;
				}
				ofxOscMessage m;
				m.setAddress("/live/volume");
				m.addIntArg(i);
				m.addFloatArg(ofClamp(volume, 0.0f, 1.0f));
				osc_sender.sendMessage(m);
			}
		}	
		/**
		 * The number of AbletonTrackInfo instances currently active.
		 * @return The number of AbletonTrackInfo instances currently active.
		 */
		unsigned int infoSize()
		{
			return info.size();
		}
		wezside::AbletonTrackInfo* getInfoForGroup(int group_index)
		{
			int lookup_index = trackIndexForGroup(group_index);
			if ((unsigned)lookup_index < info.size() && info.size() > 0)
			{
				return &info.at(lookup_index);
			} 
			return NULL;
		}
		wezside::AbletonTrackInfo* getInfoForTrack(int track_index)
		{
			if ((unsigned)track_index < info.size())
			{
				return &info.at(track_index);
			}
			return NULL;
		}
		unsigned int getGroupSize()
		{
			return groups.size();
		}
		std::string getGroupName(int index)
		{
			int i = trackIndexForGroup(index);
			return trackArr.size() == 0 ? "" : trackArr.get<jsonxx::Object>(i).get<jsonxx::String>("track_name");
		}
		/**
		 * This function will add a group to the JSON object and associate an index with this
		 * @param std::string [description]
		 */
		void assignGroup(std::string group_name)
		{
			groups.push_back(group_name);
		}
		/**
		 * This will return the total tracks contained within a group excluding the group itself.
		 * @param  group_index The group zero index to calculate total tracks for
		 * @return             Total number of tracks allocated to this group
		 */
		int getGroupTrackSize(int index)
		{
			int track_count = 0;
			int lookup_index = trackIndexForGroup(index);
			for (unsigned int i = lookup_index+1; i < trackArr.size(); ++i)
			{
				if (trackArr.get<jsonxx::Object>(i).has<jsonxx::Boolean>("group"))
				{
					break;
				}
				track_count++;
			}
			return track_count;
		}
	};
}
#endif // __OSCCONTROLLER_HPP__