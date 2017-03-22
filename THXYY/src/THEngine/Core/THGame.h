#ifndef THGAME_H
#define THGAME_H

#include "../Common/THCommon.h"
#include "../Platform/THApplication.h"
#include "../Platform/THInput.h"
#include "../Platform/THAudio.h"
#include "THScene.h"
#include "THFont.h"
#include "THSprite.h"
#include "THDataStack.h"
#include "../Renderer/THSpriteRenderer.h"
#include "../Renderer/THParticle3DRenderer.h"
#include "../Renderer/THMeshRenderer.h"
#include <Renderer\THRenderPipeline.h>
#include <Renderer\THSkyBoxRenderer.h>
#include "../Asset/THAssetManager.h"
#include "../UI/THEventSystem.h"
#include <Platform\THCoreDumper.h>


namespace THEngine
{
	class Font;

	class Game : public EngineObject
	{
	private:
		static Game* instance;
		String title;
		int width, height;
		bool fullScreen;

		bool enterBackground = false;

		float fps;
		int frameCount;
		bool showFPS;
		
		unsigned int lastTime, currentTime;

		CoreDumper coreDumper;

		Application* app;

		Scene* scene;
		Scene* nextScene;

		RenderPipeline* pipeline = nullptr;

		AssetManager* assetManager;

		EventSystem* eventSystem;

		Font* defaultFont;

		Input* input;

		Audio* audio = nullptr;

		ExceptionManager* exceptionManager = nullptr;

		DataStack* dataStack = nullptr;

	private:
		void CalcFPS();
		void DrawFPS();

	public:
		using RenderQueueType = RenderPipeline::RenderQueueType;

	public:
		Game();
		virtual ~Game();

		virtual void Update() override;
		virtual void Draw() override;
		virtual void OnShutdown();
		virtual void OnEnterBackground();
		virtual void OnReturnToForeground();

		int Run();

		void Shutdown();

		inline void Quit()
		{
			app->Quit();
		}

		static Game* GetInstance();

		bool CreateGame(int width, int height, bool fullScreen, const String& title, int bigIcon, int smallIcon);

		void SetScene(Scene* scene);

		void LoadScene(Scene* scene);

		inline Application* GetApplication() const { return app; }

		inline RenderPipeline* GetRenderPipeline() const { return pipeline; }

		inline AssetManager* GetAssetManager() const
		{
			return assetManager;
		}

		inline int GetWidth() const { return width; }

		inline int GetHeight() const { return height; }

		inline Scene* GetScene() const { return scene; }

		inline const String& GetTitle() const { return title; }
	};
}

#endif