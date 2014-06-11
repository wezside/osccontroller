#ifndef __ABLETON_TRACK_HPP__
#define __ABLETON_TRACK_HPP__

namespace wezside
{
	class AbletonTrack
	{
	private:

	public:
		AbletonTrack() {}
	 	AbletonTrack(const AbletonTrack& s) {}
		AbletonTrack& operator=(AbletonTrack& s){return s;}
		~AbletonTrack() {}

		void update(){}
		void draw(){}
	};
}
#endif // __ABLETON_TRACK_HPP__