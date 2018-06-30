#ifndef THAUDIO_H
#define THAUDIO_H

#include <Common\THCommon.h>
#include <xaudio2.h>
#include "THSound.h"
#include "THMusic.h"
#include <queue>
#include <unordered_map>

namespace THEngine
{
	class Audio : public Object, public Singleton<Audio>
	{
		friend class Singleton<Audio>;

	private:
		IXAudio2 * xaudio = nullptr;
		IXAudio2MasteringVoice* masterVoice = nullptr;

		std::queue<Ptr<Sound>> playQueue;

		int volume = 50;    //Range from 0 to 100
		int musicVolume = 50;

		Ptr<Music> currentMusic;
		std::unordered_map<int, Ptr<Sound>> channelSoundMap;

	private:
		Audio() = default;
		Ptr<Sound> LoadWav(const String& filePath);

		void SendToPlayQueue(Ptr<Sound> sound) { this->playQueue.push(sound); }
		static void OnChannelFinished(int channel);

		void PlayMusic(Ptr<Music> music);
		void PlayMusic(Ptr<Music> music, bool looped);
		void StopMusic(Ptr<Music> music);

		void OnMusicFinished();

	public:
		virtual ~Audio();

		bool Init();

		Ptr<Sound> CreateSound(const String& filePath);
		Ptr<Music> CreateMusic(const String& filePath);

		inline void SetVolume(int volume) { this->volume = volume; }

		inline Ptr<Music> GetCurrentMusic() const { return this->currentMusic; }

		void Update();

		friend class Sound;
		friend class Music;
	};
}

#endif