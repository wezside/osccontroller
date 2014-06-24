#ifndef __ABLETONTRACK_INFO_HPP__
#define __ABLETONTRACK_INFO_HPP__

namespace wezside
{
	class AbletonTrackInfo
	{
	private:
		int index;
		float volume;		
		std::string name;

	public:
		AbletonTrackInfo() 
		{
			name = "";
			index = -1;
			volume = 0.0f;
		}
		AbletonTrackInfo(std::string n, int i, float v = 0.0f) 
		{
			name = n;
			index = i;
			volume = v;			
			ofLog(OF_LOG_NOTICE, "Track %d added", index);	
		}

		~AbletonTrackInfo() {}

		int getIndex() {return index;}
		float getVolume() {return volume;}
		void setVolume(float v) {volume = v;}
	};
}
#endif // __ABLETONTRACK_INFO_HPP__