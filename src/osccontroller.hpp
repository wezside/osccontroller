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
		void setTrackVolume(int track, float volume)
		{
			ofxOscMessage m;
			m.setAddress("/live/volume");
			m.addIntArg(track);
			m.addFloatArg(ofClamp(volume, 0.0f, 1.0f));
			osc_sender.sendMessage(m);
		}
		void setGroupVolume(int index, float volume)
		{
			jsonxx::Array groupArr = mapping.get<jsonxx::Array>("data");
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
	};
}
#endif // __OSCCONTROLLER_HPP__