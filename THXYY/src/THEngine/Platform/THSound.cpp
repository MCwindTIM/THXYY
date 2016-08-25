#include "THSound.h"

namespace THEngine
{
	Sound::Sound()
	{

	}

	Sound::~Sound()
	{
		TH_SAFE_RELEASE(buffer);
	}

	void Sound::Play()
	{
		DWORD status;
		buffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)
		{
			buffer->SetCurrentPosition(0);
		}
		buffer->Play(0, 0, 0);
	}
}

