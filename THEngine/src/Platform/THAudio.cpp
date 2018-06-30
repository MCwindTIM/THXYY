#include "THAudio.h"
#include "THApplication.h"
#include <External\SDL2\SDL.h>
#include <External\SDL2\SDL_mixer.h>

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2_mixer.lib")

namespace THEngine
{
	Audio::~Audio()
	{
		if (masterVoice)
		{
			masterVoice->DestroyVoice();
		}
		TH_SAFE_RELEASE(xaudio);

		Mix_HookMusicFinished(nullptr);
		Mix_ChannelFinished(nullptr);
		Mix_AllocateChannels(32);

		Mix_CloseAudio();
	}

	bool Audio::Init()
	{
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
			return false;

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			return false;
		}
		Mix_Volume(-1, this->volume / 100.0f * MIX_MAX_VOLUME);

		Mix_HookMusicFinished([]() {
			auto audio = Audio::GetInstance();
			audio->OnMusicFinished();
		});

		Mix_ChannelFinished(Audio::OnChannelFinished);

		return true;
	}

	void Audio::OnChannelFinished(int channel)
	{
		auto audio = Audio::GetInstance();
		auto iter = audio->channelSoundMap.find(channel);
		if (iter != audio->channelSoundMap.end())
		{
			iter->second->channel = -1;
			audio->channelSoundMap.erase(iter);
		}
	}

	Ptr<Sound> Audio::CreateSound(const String& filePath)
	{
		auto exceptionManager = ExceptionManager::GetInstance();
		Ptr<Sound> sound;

		String ext = filePath.SubString(filePath.LastIndexOf(TCHAR('.')) + 1, filePath.GetLength());
		if (ext == "wav")
		{
			sound = LoadWav(filePath);
		}
		else
		{
			Ptr<Exception> exception = Ptr<Exception>::New("不支持的文件格式。");
			exceptionManager->PushException(exception);
		}

		if (sound != nullptr)
		{
			sound->SetVolume(volume);
		}
		else
		{
			auto exception = exceptionManager->GetException();
			if (exception != nullptr)
			{
				THMessageBox((String)"无法加载音频文件：" + filePath + "原因是：\n" + exception->GetInfo());
				exceptionManager->SetHandled();
			}
		}
		return sound;
	}

	Ptr<Sound> Audio::LoadWav(const String& filePath)
	{
		Ptr<Sound> sound = Ptr<Sound>::New();
		auto exceptionManager = ExceptionManager::GetInstance();

		sound->chunk = Mix_LoadWAV(filePath.ToStdString().c_str());
		if (sound->chunk == nullptr)
		{
			Ptr<Exception> exception = Ptr<Exception>::New(Mix_GetError());
			exceptionManager->PushException(exception);
			return nullptr;
		}

		return sound;
	}

	Ptr<Music> Audio::CreateMusic(const String& filePath)
	{
		auto exceptionManager = ExceptionManager::GetInstance();
		Ptr<Music> music = Ptr<Music>::New();

		char path[256];
		WideCharToMultiByte(CP_ACP, 0, filePath.GetBuffer(), -1, path, sizeof(path), NULL, NULL);
		music->mixMusic = Mix_LoadMUS(path);
		if (music->mixMusic == nullptr)
		{
			exceptionManager->PushException(Ptr<Exception>::New(((String)"无法加载音频文件：" + filePath)));
			return nullptr;
		}

		return music;
	}

	void Audio::PlayMusic(Ptr<Music> music)
	{
		PlayMusic(music, false);
	}

	void Audio::PlayMusic(Ptr<Music> music, bool looped)
	{
		if (currentMusic == music && Mix_PlayingMusic() == 1)
			return;

		if (currentMusic != nullptr && currentMusic != music)
		{
			currentMusic->Stop();
		}
		currentMusic = music;

		if (looped)
		{
			Mix_PlayMusic(music->mixMusic, -1);
		}
		else
		{
			Mix_PlayMusic(music->mixMusic, 1);
		}
		float volume = music->volume * this->musicVolume / 10000.0f;
		Mix_VolumeMusic(volume * MIX_MAX_VOLUME);
	}

	void Audio::OnMusicFinished()
	{
		this->currentMusic = nullptr;
	}

	void Audio::StopMusic(Ptr<Music> music)
	{
		if (currentMusic != music)
			return;

		if (music != nullptr)
		{
			Mix_HaltMusic();
		}
		currentMusic = nullptr;
	}

	void Audio::Update()
	{
		while (!this->playQueue.empty())
		{
			Ptr<Sound> sound = this->playQueue.front();
			this->playQueue.pop();
			if (sound->channel >= 0)
			{
				Mix_HaltChannel(sound->channel);
				Mix_PlayChannel(sound->channel, sound->chunk, 0);
			}
			else
			{
				sound->channel = Mix_PlayChannel(sound->channel, sound->chunk, 0);
			}
			sound->submitted = false;
		}
	}
}