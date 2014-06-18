#ifndef __ABLETON_GROUP_HPP__
#define __ABLETON_GROUP_HPP__

#include "abletontrack.hpp"
#include "abletontrackinfo.hpp"

namespace wezside
{
	class AbletonGroup
	{
	private:
		bool beat;
		std::string group_name;
		std::vector<wezside::AbletonTrack> tracks;
		std::vector<wezside::AbletonTrackInfo> info;

	public:
		AbletonGroup(std::string n) : group_name(n) {}
		~AbletonGroup() {}

		void setInfo(std::vector<wezside::AbletonTrackInfo>& tracks_info)
		{
			info = tracks_info;
		}
		void setBeat(bool b)
		{
			beat = b;
		}
		void update()
		{
			for(vector<wezside::AbletonTrack>::iterator it = tracks.begin(); it != tracks.end(); it++)
			{
				(*it).update();
			}
		}
		void draw(int xoffset, int yoffset)
		{
			int w = 90;
			int h = 256;

			ofNoFill();
			ofSetColor(255.0, 122.0);
			ofRect(xoffset, yoffset, w, h);

			int count = 1;
			int xoff = xoffset;
			int yoff = yoffset;
			int track_width = 30;
			int track_height = 30;
			for(vector<wezside::AbletonTrack>::iterator it = tracks.begin(); it != tracks.end(); it++)
			{
				(*it).draw(xoff + 10, yoff + 10);
				ofSetColor(255.0);
				ofDrawBitmapString(ofToString(count), xoff + 20, yoff + 30);
				if ((count) % 2 == 0)
				{
					xoff = xoffset;
					yoff += track_height + 10;
				}
				else xoff += track_width + 10;
				count++;
			}
			ofSetColor(255.0);
			ofDrawBitmapString(group_name.c_str(), xoffset, yoffset + 270);
		}
		void addTrack(wezside::AbletonTrack track) 
		{
			tracks.push_back(track);
		}
	};
}
#endif // __ABLETON_GROUP_HPP__