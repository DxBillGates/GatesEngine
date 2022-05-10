#pragma once
#include "..\Audio\Audio.h"
#include <string>
#include <vector>
#include <map>

namespace GE
{
	class AudioManager
	{
	private:
		std::map<std::string,Audio*> audios;
		std::map <std::string, AudioData*> backupAudioDatas;
	public:
		AudioManager();
		~AudioManager();
		Audio* AddAudio(Audio* newAudio);
		AudioData* AddAudioData(AudioData* newAudioData,const std::string& tag);
		AudioData* GetAudioData(std::string& tag);
		Audio* Use(const std::string& tag);
	};
}
