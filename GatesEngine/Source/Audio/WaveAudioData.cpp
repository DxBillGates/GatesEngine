#include "..\..\Header\Audio\WaveAudioData.h"

GE::AudioData::AudioData(const char * filepath)
{
	using namespace std;

	RiffHeader riffHeader;
	FormatChunk fmtChunk;
	Chunk chunk;

	ifstream file;
	file.open(filepath, ios_base::binary);
	Skip("RIFF", file);
	file.read((char*)&riffHeader, sizeof(riffHeader));
	Skip("fmt ", file);
	file.read((char*)&fmtChunk, sizeof(fmtChunk));
	Skip("data", file);
	file.read((char*)&chunk, sizeof(chunk));

	//波形データの読み込み
	buffer = new char[chunk.size];
	file.read(buffer, chunk.size);
	file.close();

	memcpy(&waveFormatEx, &fmtChunk.fmt, sizeof(fmtChunk.fmt));
	waveFormatEx.wBitsPerSample = waveFormatEx.nBlockAlign * 8 / waveFormatEx.nChannels;

	audioBuffer.pAudioData = (BYTE*)buffer;
	audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
	audioBuffer.AudioBytes = chunk.size;
}

GE::AudioData::~AudioData()
{
	delete[] buffer;
}

WAVEFORMATEX * GE::AudioData::GetWaveFormatEx()
{
	return &waveFormatEx;
}

XAUDIO2_BUFFER * GE::AudioData::GetAudioBuffer()
{
	return &audioBuffer;
}

char * GE::AudioData::GetBuffer()
{
	return buffer;
}

void GE::AudioData::Skip(std::string target, std::ifstream & file)
{
	auto currentPos = file.tellg();
	std::string s = "";
	int i = 0;

	// targetで指定された文字に到達するまでファイルを走査
	while (s != target && !file.eof())
	{
		char read;
		file.read((char*)&read, sizeof(read));
		if (read == target[i])
		{
			++i;
			s += read;
		}
		else
		{
			i = 0;
			s = "";
		}
	}

	if (s == target)
	{
		int size = (int)target.size();
		Skip(-(size), file);
	}
	else
	{
		file.seekg(((int)currentPos), std::ios_base::beg);
	}
}

void GE::AudioData::Skip(int byte, std::ifstream & file)
{
	auto currentPos = file.tellg();
	file.seekg((((int)currentPos) + (uint64_t)byte), std::ios_base::beg);
}
