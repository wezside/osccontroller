#pragma once

#include "ofMain.h"
#include "osccontroller.hpp"
#include "abletongroup.hpp"
#include "abletontrack.hpp"

class ofApp : public ofBaseApp{

	public:
		void exit();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		std::vector<wezside::AbletonGroup> groups;
		wezside::OSCController oscremote;
};
