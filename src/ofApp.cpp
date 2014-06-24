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
		for (unsigned int i = 0; i < oscremote.getGroupSize(); ++i)
		{
			if (oscremote.getGroupName(i) == "") continue;
			wezside::AbletonGroup g(oscremote.getGroupName(i));
			for (int k = 0; k < oscremote.getGroupTrackSize(i); ++k)
			{
				g.addTrack(k, wezside::AbletonTrack(), oscremote.getGroupTrackSize(i));
			}
			groups.push_back(g);
			groups.at(i).setGroupInfo(oscremote.getInfoForGroup(i));

			// Sets all group volume down 
			if (i == 1)
			{
	 			oscremote.setGroupVolume(i, 0.5f, true, true);
			}
		}
	}

	// Poll the group track volume 
	if (ofGetFrameNum() % 90 == 0 && groups.size() == oscremote.getGroupSize())
	{
		int group_start_index = 0;
		for (unsigned int i = 0; i < oscremote.getGroupSize(); ++i)
		{
			// Fetch the group volume
			// oscremote.getGroupVolume(i);

			// Fetch and set the group info object
			groups.at(i).setGroupInfo(oscremote.getInfoForGroup(i));
			
			// Fetch and set the track info objects for each group
			for (int k = 0; k < oscremote.getGroupTrackSize(i); ++k)
			{
				oscremote.getTrackVolume(i+1+k);
				ofLog(OF_LOG_NOTICE, "%s %d", "Updating track info for ", group_start_index+1+k);
				groups.at(i).addTrackInfo(k, oscremote.getInfoForTrack(group_start_index+1+k));
			}
			group_start_index += oscremote.getGroupTrackSize(i) + 1;
			groups.at(i).update();
		}
	}
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

	// Draw the beat/tempo
	if (oscremote.getBeat())
	{
		ofFill();
		ofSetColor(255.0f);
		ofCircle(ofGetWindowWidth() - 40, 0, 10);
		oscremote.setBeat(false);
	}
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