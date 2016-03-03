#pragma once

#pragma comment(lib,"dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include<Windows.h>
#include<mmsystem.h>
#include<dsound.h>
#include<stdio.h>


class cSound
{
public:
	cSound();
	cSound(const cSound&);
	~cSound();
	void shutdown();
	bool iniDirectSound(HWND);
	void load(int sndCode, char* fileName);
	void play(int sndCode, int intensity);
	void stop(int sndCode);
	void stopa();
	void resume();
	bool stopped[500];
private:
	IDirectSound8 * intSound;
	IDirectSoundBuffer* primaryBuffer;
	IDirectSoundBuffer8* secondaryBuffer;
	bool loadWav(char*, IDirectSoundBuffer8**);
	void playSnd(int,IDirectSoundBuffer8*);
	struct wavFileHeader
	{
		char chunkId[4];				//RIFF
		unsigned long chunkSize;		//The size of the subchunk following it minus 8 of its
		char format[4];					//WAVE
		char subChunkId[4];				//FMT_
		unsigned long subChunkSize;    //16 For PCM
		unsigned short audioFormat;		//PCM=1,Linear Quantization
		unsigned short numChannels;		//No of channels 
		unsigned long sampleRate;
		unsigned long bytesPerSecond;	//sampleRate*bitsPerSample*numChannels/8
		unsigned short blockAlign;		//Size of each sample including all channels in byte
		unsigned short bitsPerSample;	//Size of each sample in bits
		char dataChunkId[4];			//Contains text  data
		unsigned long dataSize;

	};

	class arrBuffer
	{
	public:
		arrBuffer()
		{
			secBuffer=NULL;
			sndCode;
			next=NULL;
		}

		IDirectSoundBuffer8* secBuffer;
		int sndCode;
		arrBuffer* next;
	};
	arrBuffer* sndBuffers;
};