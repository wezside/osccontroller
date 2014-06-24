#ifndef __ABLETON_TRACK_HPP__
#define __ABLETON_TRACK_HPP__

namespace wezside
{
	class AbletonTrack
	{
	private:
		wezside::AbletonTrackInfo* info;

	public:
		AbletonTrack() {}
		~AbletonTrack() {}

		void update(){}
		void draw(int xoffset, int yoffset)
		{
			int w = 30;
			int h = 30;
			ofFill();
			float v = info->getVolume();
			if (v == 0.0f)
			{
				ofSetColor(33.0, v * 255.0f);
			}
			else ofSetColor(255.0f, 133.0f, 0.0f, v * 255.0f);
			ofRect(xoffset, yoffset, w, h);
		}
		void setInfo(wezside::AbletonTrackInfo* track_info)
		{
			info = track_info;
		}
	};
}
#endif // __ABLETON_TRACK_HPP__