#ifndef __OSCCONTROLLER_HPP__
#define __OSCCONTROLLER_HPP__

#include <fstream>

#include "ofxOsc.h"
#include "jsonxx.h"

#define HOST "192.168.0.227"
#define PORT 9000

namespace wezside
{
	class OSCController
	{
	private:
		jsonxx::Object mapping;
		jsonxx::Array groupArr;
		ofxOscSender osc_sender;

	public:
		OSCController() {}
		OSCController(const OSCController& s) {}
		OSCController& operator=(OSCController& s){return s;}
		~OSCController() {}

		void init()
		{
			osc_sender.setup(HOST, PORT);
			ofxOscMessage m;
			m.setAddress("/live/play");
			osc_sender.sendMessage(m);
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
			groupArr = mapping.get<jsonxx::Array>("data");
		}
		void stop()
		{
			ofxOscMessage m;
			m.setAddress("/live/stop");
			osc_sender.sendMessage(m);
		}
		void liveoscAPI(std::string address, int valint = -1, float valfloat = -99999.0f)
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
		 * Sets the group volume. Only use if an ableton JSON mapping file is used.
		 * @param index  Group Index
		 * @param volume Float value for volume in range 0.0 to 1.0
		 */
		void setGroupVolume(int index, float volume)
		{
			
			int groupIndex = 0;
			for (int i = 0; i < index; ++i)
			{
				groupIndex += 1; // the group itself
				groupIndex += groupArr.get<jsonxx::Object>(i).get<jsonxx::Array>("tracks").size(); // total tracks within group
				ofLog(OF_LOG_NOTICE, "Group size %d", groupArr.get<jsonxx::Object>(i).get<jsonxx::Array>("tracks").size());
			}
			ofLog(OF_LOG_NOTICE, "Group Index %d", groupIndex);
			ofxOscMessage m;
			m.setAddress("/live/volume");
			m.addIntArg(groupIndex);
			m.addFloatArg(ofClamp(volume, 0.0f, 1.0f));
			osc_sender.sendMessage(m);
		}	
		int getGroupSize()
		{
			return mapping.get<jsonxx::Array>("data").size();
		}
		std::string getGroupName(int index)
		{
			return groupArr.get<jsonxx::Object>(index).get<jsonxx::String>("group");
		}
	};
}
#endif // __OSCCONTROLLER_HPP__