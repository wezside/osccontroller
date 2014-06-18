#include "ofApp.h"

void ofApp::exit()
{
	oscremote.stop();
}
void ofApp::setup()
{
	ofBackground(33);
	ofSetCircleResolution(100);

	// Initialise OSC communication
	oscremote.init();

	// Group assignments must be made before /live/name/track call
	oscremote.assignGroup("Ambient");
	oscremote.assignGroup("Speaker 1");
	oscremote.assignGroup("Speaker 2");

	// Total number of tracks
	oscremote.liveOSCAPI("/live/tracks");

	// Returns all the track names
	oscremote.liveOSCAPI("/live/name/track");

	// Start the Ableton live session
	oscremote.start();
}
void ofApp::update()
{
	if (groups.size() != oscremote.getGroupSize())
	{
		// Visual representation for Ableton Live session set-up
		for (int i = 0; i < oscremote.getGroupSize(); ++i)
		{
			if (oscremote.getGroupName(i) == "") continue;
			wezside::AbletonGroup g(oscremote.getGroupName(i));
			ofLog(OF_LOG_NOTICE, "AbletonGroup '%s' added", oscremote.getGroupName(i).c_str());
			ofLog(OF_LOG_NOTICE, "Track count [%d] for group %d", oscremote.getTrackSize(i), i);
			for (int k = 0; k < oscremote.getTrackSize(i); ++k)
			{
				g.addTrack(wezside::AbletonTrack());
			}
			groups.push_back(g);

			// Assumes ambient group is first and
			// all groups are in collapsed view in Ableton
			/*if (i > 0)
			{
				// oscremote.listen();
	 			oscremote.setTrackVolume(i, 0.0f);
			}*/
		}
	}


	// Visual representation for Ableton Live session set-up
/*	if (ofGetFrameNum() % 90 == 0)
	{
		for (int i = 0; i < oscremote.getGroupSize(); ++i)
		{
			oscremote.getTrackVolume(i);
			groups.at(i).setBeat(oscremote.getBeat());
		}
	}*/
	oscremote.listen();
}
void ofApp::draw()
{
	ofTranslate(20, 20);
	int xoffset = 0;
	int yoffset = 0;
	int count = 1;
	for(vector<wezside::AbletonGroup>::iterator it = groups.begin(); it != groups.end(); it++)
	{
		(*it).draw(xoffset, yoffset);
		if (count % (ofGetWindowWidth() / 100) == 0)
		{
			yoffset += 280;
			xoffset = 0;
		}
		else xoffset += 110; 
		count ++;
	}
	oscremote.drawBeat();
}
void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key)
{
	switch(key)
	{
		case '0': break;
		case '1': break;
		case '2': break;
	}
}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg)
{
	ofLog(OF_LOG_NOTICE, "%s", "Got message");
}
void ofApp::dragEvent(ofDragInfo dragInfo){}