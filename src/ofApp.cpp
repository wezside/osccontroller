#include "ofApp.h"

void ofApp::exit()
{
	oscremote.stop();
}
void ofApp::setup()
{
	ofBackground(33);
	oscremote.init();
	oscremote.load(ofToDataPath("ableton.json"));
	ofLog(OF_LOG_NOTICE, "%d", oscremote.getGroupSize());
}
void ofApp::update()
{

}
void ofApp::draw()
{

}
void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key)
{
	switch(key)
	{
		case '0': oscremote.setGroupVolume(0, 0.5f); break;
		case '1': oscremote.setGroupVolume(1, 0.5f); break;
		case '2': oscremote.setGroupVolume(2, 0.5f); break;
	}
}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}