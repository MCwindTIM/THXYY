#ifndef THAUDIO_H
#define THAUDIO_H

#include "../Common/THCommon.h"
#include <dsound.h>
#include "THSound.h"

namespace THEngine
{
	class Audio : public Object
	{
	private:
		static Audio* instance;

		IDirectSound* dsound = nullptr;

		ArrayList<Sound*> soundList;

		int volume = 20;    //Range from 0 to 100

	private:
		Audio();
		bool Init();

		Sound* LoadWav(String filePath);

		

	public:
		virtual ~Audio();

		static Audio* GetInstance();

		Sound* CreateSound(String filePath);

		inline void DestroySound(Sound* sound)
		{
			soundList.Remove(sound);
		}

		inline void SetVolume(int volume) { this->volume = volume; }
	};
}

#endif