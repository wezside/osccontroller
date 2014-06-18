#ifndef __ABLETON_TRACK_HPP__
#define __ABLETON_TRACK_HPP__

namespace wezside
{
	class AbletonTrack
	{
	private:

	public:
		AbletonTrack() {}
		~AbletonTrack() {}

		void update(){}
		void draw(int xoffset, int yoffset)
		{
			int w = 30;
			int h = 30;
			ofFill();
			ofSetColor(255.0, 122.0);
			ofRect(xoffset, yoffset, w, h);
		}
		void drawBeat(bool beat = true, float volume = 0.0f)
		{
			/*if (beat)
			{
				h = 
			}
			ofRect(xoffset, yoffset, w, h);	*/
		}
	};
}
#endif // __ABLETON_TRACK_HPP__