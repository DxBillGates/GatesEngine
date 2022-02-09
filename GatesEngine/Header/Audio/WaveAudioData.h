#pragma once
#include <fstream>
#include <sstream>
#include <xaudio2.h>
#include <mmsystem.h>
namespace GE
{

	struct Chunk
	{
		char id[4];
		int32_t size;
	};

	struct RiffHeader
	{
		Chunk chunk;
		char tyip[4];
	};

	struct FormatChunk
	{
		Chunk chunk;
		WAVEFORMAT fmt;
	};


	class AudioData
	{
	private:
		WAVEFORMATEX waveFormatEx;
		XAUDIO2_BUFFER audioBuffer;
		char* buffer;
	public:
		AudioData(const char* filepath);
		~AudioData();
		WAVEFORMATEX* GetWaveFormatEx();
		XAUDIO2_BUFFER* GetAudioBuffer();
		char* GetBuffer();
		void Skip(std::string target, std::ifstream& file);
		void Skip(int byte, std::ifstream& file);
	};

}