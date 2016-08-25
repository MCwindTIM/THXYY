#ifndef THSOUND_H
#define THSOUND_H

#include "../Common/THCommon.h"
#include <dsound.h>

namespace THEngine
{
	class Sound : public Object
	{
	private:
		IDirectSoundBuffer* buffer = nullptr;

	public:
		Sound();
		virtual ~Sound();

		inline void SetVolume(int volume)
		{
			buffer->SetVolume((DWORD)(-30 * (100 - volume)));
		}

		void Play();

		inline void Stop() { buffer->Stop(); }

		friend class Audio;
	};
}

#endif