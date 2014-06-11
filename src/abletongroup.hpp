#ifndef __ABLETON_GROUP_HPP__
#define __ABLETON_GROUP_HPP__

#include "abletontrack.hpp"

namespace wezside
{
	class AbletonGroup
	{
	private:
		std::string name;
		std::vector<wezside::AbletonTrack> tracks;

	public:
		AbletonGroup(std::string n) : name(n) {ofLog(OF_LOG_NOTICE, "%s", n.c_str());}
	 	AbletonGroup(const AbletonGroup& s) {}
		AbletonGroup& operator=(AbletonGroup& s){return s;}
		~AbletonGroup() {}

		void update(){}
		void draw(){}

		void addTrack(wezside::AbletonTrack track) 
		{
			tracks.push_back(track);
		}
	};
}
#endif // __ABLETON_GROUP_HPP__