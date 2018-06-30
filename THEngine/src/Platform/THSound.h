#ifndef THSOUND_H
#define THSOUND_H

#include <Common\THCommon.h>
#include <SDL2\SDL_mixer.h>

namespace THEngine
{
	class Sound : public Object
	{
	private:
		Mix_Chunk * chunk = nullptr;
		int channel = -1;
		bool submitted = false;

	public:
		Sound();
		virtual ~Sound();

		void SetVolume(int volume);

		void Play();

		friend class Audio;
	};
}

#endif