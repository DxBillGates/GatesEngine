#pragma once
#include "WaveAudioData.h"
#include <string>

namespace GE
{
	class Audio : public IXAudio2VoiceCallback
	{
	private:
		static IXAudio2* xAudioEngine;
		static IXAudio2MasteringVoice* masterVoice;
		IXAudio2SourceVoice* sourceVoice;
		AudioData* pSoundData;
		bool isStart;
		bool isPlay;
		bool isEnd;
		std::string tag;
	public:
		Audio(AudioData* soundData,const std::string& tag);
		~Audio();
		static void SetAudioEngine();
		void CreateVoice();
		void Start();
		bool GetIsStart();
		bool GetIsPlay();
		bool GetIsEnd();
		const std::string& GetTag();
		IXAudio2SourceVoice* GetSourceVoice();
		void SetVolume(float value);
		void SetPitch(float value);
	private:
		STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired){}
		STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {}
		STDMETHOD_(void, OnStreamEnd) (THIS) {}
		STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext)
		{
			isStart = true;
			isPlay = true;
			isEnd = false;
		}
		STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
		{
			isStart = false;
			isPlay = false;
			isEnd = true;
		}
		STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {}
		STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {}
	};

}