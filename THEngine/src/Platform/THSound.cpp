#include "THSound.h"
#include "THAudio.h"

namespace THEngine
{
	Sound::Sound()
	{
	}

	Sound::~Sound()
	{
		if (this->chunk)
		{
			Mix_FreeChunk(this->chunk);
			this->chunk = nullptr;
		}
	}

	void Sound::SetVolume(int volume)
	{
		auto audio = Audio::GetInstance();

		Mix_VolumeChunk(this->chunk, volume * audio->volume / 10000.0f * MIX_MAX_VOLUME);
	}

	void Sound::Play()
	{
		auto audio = Audio::GetInstance();
		if (submitted == false)
		{
			audio->SendToPlayQueue(this);
			submitted = true;
		}
	}
}