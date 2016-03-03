#include"sound.h"
#include<assert.h>
cSound::cSound()
{
	primaryBuffer = NULL;
	secondaryBuffer = NULL;
	intSound = NULL;
	sndBuffers=NULL;
}
cSound::cSound(const cSound &x)
{
}
cSound::~cSound()
{
}

void cSound::shutdown()
{
	if (secondaryBuffer)
	{
		secondaryBuffer->Release();
		delete secondaryBuffer;
	}
	if (primaryBuffer)
	{
		primaryBuffer->Release();
		delete primaryBuffer;
	}
	if (intSound)
	{
		intSound->Release();
		delete intSound;
	}
}

void cSound::load(int sndCode, char* fileName)
{
	arrBuffer* tmp = sndBuffers;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			if (tmp->sndCode == sndCode)
				assert(0 && "sndCode already loaded. Please choose someother code");
			tmp = tmp->next;
		}
		if (tmp->sndCode == sndCode)
			assert(0 && "sndCode already loaded. Please choose someother code");
		tmp->next = new arrBuffer;
		tmp = tmp->next;
	}
	else
	{
		sndBuffers = new arrBuffer;
		tmp = sndBuffers;
	}
	tmp->sndCode = sndCode;
	if (!loadWav(fileName, &tmp->secBuffer))
		assert(0 && "Snd File Can't Be Accessed");
}

void cSound::play(int sndCode, int intensity)
{
	arrBuffer* tmp = sndBuffers;
	while (tmp->sndCode != sndCode&&tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	if (tmp->sndCode != sndCode)
		assert(0 && "No Sound Buffer Found For The Given sndCode Value!!!");
	else
		playSnd(intensity, tmp->secBuffer);
}

void cSound::stopa()
{
	arrBuffer* tmp = sndBuffers;
	DWORD tmp1;

	while (tmp->next != NULL)
	{
		
		tmp->secBuffer->GetStatus(&tmp1);
		if (tmp1 == DSBSTATUS_PLAYING)
		{
			stopped[tmp->sndCode] = true;
			tmp->secBuffer->Stop();
		}
		tmp = tmp->next;
	}
}

void cSound::resume()
{
	arrBuffer* tmp = sndBuffers;
	while (tmp->next != NULL)
	{
		if (stopped[tmp->sndCode] == true)

		{
			tmp->secBuffer->Play(0, 0, 0);
			stopped[tmp->sndCode] = false;
		}
		tmp = tmp->next;
	}
}

void cSound::stop(int sndCode)
{
	arrBuffer* tmp = sndBuffers;
	while (tmp->sndCode != sndCode&&tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	if (tmp->sndCode != sndCode)
		assert(0 && "No Sound Buffer Found For The Given sndCode Value!!!");
	else
	{
		tmp->secBuffer->Stop();
		stopped[tmp->sndCode] == false;
	}
}

bool cSound::iniDirectSound(HWND hWnd)
{
	for (int i = 0; i < 500; i++)
		stopped[i] = false;
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX wavFormat;
	result=DirectSoundCreate8(NULL, &intSound, NULL);
	if (FAILED(result))return false;
	result=intSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if (FAILED(result))return false;
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;  //For primary
	bufferDesc.dwBufferBytes = 0;  //For primary 0
	bufferDesc.dwReserved = 0;//For primary 0
	bufferDesc.lpwfxFormat = NULL;//For Primary NULL
	bufferDesc.guid3DAlgorithm = GUID_NULL;//For Primary without 3d functions
	result=intSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
	if (FAILED(result))return false;
	wavFormat.wFormatTag = WAVE_FORMAT_PCM;
	wavFormat.nSamplesPerSec = 44100;
	wavFormat.wBitsPerSample = 16;
	wavFormat.nChannels = 2;
	wavFormat.nBlockAlign = (wavFormat.wBitsPerSample/8)*wavFormat.nChannels;
	wavFormat.nAvgBytesPerSec = wavFormat.nSamplesPerSec*wavFormat.nBlockAlign;
	wavFormat.cbSize = 0;
	result=primaryBuffer->SetFormat(&wavFormat);
	if (FAILED(result))return false;
	return true;
}

bool cSound::loadWav(char* fileName, IDirectSoundBuffer8**secondaryBuffer)
{
	int error;
	FILE *filePtr;
	unsigned int count=0;
	wavFileHeader waveFileHeader; //Stores the header of the wav file type
	WAVEFORMATEX waveFormat; //Stores the buffer wav format
	DSBUFFERDESC bufferDesc; //To sotre the details of the buffer
	IDirectSoundBuffer* tmpBuffer;
	unsigned char *waveData; //To load the wav file temporarily
	unsigned char *bufferPtr;
	unsigned long bufferSize;

	error = fopen_s(&filePtr, fileName, "rb");
	if (error!=0)
		return false;
	if (filePtr)
	count = fread(&waveFileHeader, sizeof(wavFileHeader), 1, filePtr);
	if (count != 1)
		return false;
	
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;// Check that the chunk ID is the RIFF format.
	}
		
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;// Check that the file format is the WAVE format.
	}

	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;// Check that the sub chunk ID is the fmt format.
	}

	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;// Check that the audio format is WAVE_FORMAT_PCM.
	}
	int numChannels = waveFileHeader.numChannels;
	int sampleRate = waveFileHeader.sampleRate;
	int bitsPerSample = waveFileHeader.bitsPerSample;
		
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
		return false;// Check for the data chunk header.

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = sampleRate;
	waveFormat.nChannels = numChannels;
	waveFormat.wBitsPerSample = bitsPerSample;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8)*waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nBlockAlign*waveFormat.nSamplesPerSec;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	HRESULT result;
	result = intSound->CreateSoundBuffer(&bufferDesc, &tmpBuffer, NULL);
	if (FAILED(result))return false;
	result = tmpBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if (FAILED(result))return false;
	tmpBuffer->Release();
	tmpBuffer = NULL;

	//R E A D I N G  T H E  W A V  F I L E  S T A R T S  H E R E
	fseek(filePtr, sizeof(waveFileHeader), SEEK_SET);
	waveData = new unsigned char[waveFileHeader.dataSize];
	memset(waveData, 0, waveFileHeader.dataSize);
	if(!waveData)	return false;
	while (count<waveFileHeader.dataSize)
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	error = fclose(filePtr);
	if (error != 0)return false;
	result = (*secondaryBuffer)->Lock(0,waveFileHeader.dataSize,(void**)&bufferPtr,(DWORD*)&bufferSize,NULL,0,0);
	if (FAILED(result))return false;
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);
	result = (*secondaryBuffer)->Unlock((void**)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))return false;
	delete[]waveData;

	return true;
}

void cSound::playSnd(int intensity, IDirectSoundBuffer8* secondaryBuffer)
{
	DWORD tmp;
	secondaryBuffer->GetStatus(&tmp);
	if ( tmp!= DSBSTATUS_PLAYING)
	{
		//secondaryBuffer->SetCurrentPosition(0);
		secondaryBuffer->Play(0, 0, 0);
	}
	secondaryBuffer->SetVolume(intensity);
}