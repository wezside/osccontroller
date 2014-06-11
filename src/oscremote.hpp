#ifndef __OSCREMOTE_HPP__
#define __OSCREMOTE_HPP__

#include "ofxOsc.h"

#define HOST "192.168.0.227"
#define PORT 9000

namespace wezside
{
	class OSCRemote
	{
	private:
		ofxOscSender osc_sender;

	public:
		OSCRemote() {}
	 	OSCRemote(const OSCRemote& s) {}
		OSCRemote& operator=(OSCRemote& s){return s;}
		~OSCRemote() {}

		void init()
		{
			osc_sender.setup(HOST, PORT);

			ofxOscMessage m;
			m.setAddress("/live/play");
			osc_sender.sendMessage(m);
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
	};
}
#endif // __OSCREMOTE_HPP__