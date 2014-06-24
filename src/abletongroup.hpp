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
		std::vector<wezside::AbletonTrackInfo*> info;
		wezside::AbletonTrackInfo* groupInfo;

	public:
		AbletonGroup(std::string n) : group_name(n) {}
		~AbletonGroup() {}

		void setBeat(bool b)
		{
			beat = b;
		}
		void update()
		{
			int count = 0;
			for(vector<wezside::AbletonTrack>::iterator it = tracks.begin(); it != tracks.end(); it++)
			{
				(*it).setInfo(info.at(count));
				(*it).update();
				count++;
			}
		}
		void draw(int xoffset, int yoffset)
		{
			int w = 90;
			int h = 256;

			ofNoFill();
			ofSetColor(255.0f, 122.0f);
			ofRect(xoffset, yoffset, w, h);

			ofFill();
			ofSetColor(122.0f, 122.0f, 122.0f, groupInfo->getVolume() * 255.0f);
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
		void addTrack(int index, wezside::AbletonTrack track, int total) 
		{
			if (tracks.size() == total) tracks.at(index) = track;
			else tracks.push_back(track);
		}
		void setGroupInfo(wezside::AbletonTrackInfo* group_info)
		{
			if (group_info != NULL) groupInfo = group_info;
		}
		void addTrackInfo(int index, wezside::AbletonTrackInfo* track_info)
		{
			if (track_info != NULL && index < info.size()) info.at(index) = track_info;
			else info.push_back(track_info);
		}
	};
}
#endif // __ABLETON_GROUP_HPP__