#include "..\..\Header\Audio\Audio.h"

IXAudio2* GE::Audio::xAudioEngine = nullptr;
IXAudio2MasteringVoice* GE::Audio::masterVoice = nullptr;

GE::Audio::Audio(AudioData * soundData, const std::string& tag)
	: sourceVoice(nullptr)
	, pSoundData(soundData)
	, isStart(false)
	, isPlay(false)
	, isEnd(false)
	, tag(tag)
{
	CreateVoice();
}

GE::Audio::~Audio()
{
	if (sourceVoice != nullptr)sourceVoice->Stop();
	pSoundData = nullptr;
}

void GE::Audio::SetAudioEngine()
{
	// XAudio2の動作環境をセットアップ
	XAudio2Create(&xAudioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR);
	xAudioEngine->CreateMasteringVoice(&masterVoice);
}

void GE::Audio::CreateVoice()
{
	// サウンドデータからソースボイスを作成
	HRESULT result = xAudioEngine->CreateSourceVoice(&sourceVoice, pSoundData->GetWaveFormatEx(), 0, 2.0f, &(*this));
}

void GE::Audio::Start()
{
	if (!isPlay)
	{
		isEnd = false;
		sourceVoice->SubmitSourceBuffer(pSoundData->GetAudioBuffer());
		sourceVoice->Start();
	}
}

bool GE::Audio::GetIsStart()
{
	return isStart;
}

bool GE::Audio::GetIsPlay()
{
	return isPlay;
}

bool GE::Audio::GetIsEnd()
{
	return isEnd;
}

const std::string& GE::Audio::GetTag()
{
	return tag;
}

IXAudio2SourceVoice* GE::Audio::GetSourceVoice()
{
	return sourceVoice;
}

void GE::Audio::SetVolume(float value)
{
	GetSourceVoice()->SetVolume(value);
}

void GE::Audio::SetPitch(float value)
{
	GetSourceVoice()->SetFrequencyRatio(value);
}
