#include "..\..\Header\Audio\AudioManager.h"

GE::AudioManager::AudioManager()
{
	HRESULT hr;
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	Audio::SetAudioEngine();
}

GE::AudioManager::~AudioManager()
{
	for (auto& audio : audios)
	{
		delete audio.second;
	}

	for (auto& audioData : backupAudioDatas)
	{
		delete audioData.second;
	}
	audios.clear();
	backupAudioDatas.clear();
}

GE::Audio* GE::AudioManager::AddAudio(Audio * newAudio)
{
	audios.insert(std::make_pair(newAudio->GetTag(), newAudio));
	return newAudio;
}

GE::AudioData* GE::AudioManager::AddAudioData(AudioData * newAudioData,const std::string& tag)
{
	backupAudioDatas.insert(std::make_pair(tag, newAudioData));
	return newAudioData;
}

GE::AudioData* GE::AudioManager::GetAudioData(std::string& tag)
{
	return backupAudioDatas.at(tag);
}

GE::Audio * GE::AudioManager::Use(const std::string& tag)
{
	return audios.at(tag);
}
