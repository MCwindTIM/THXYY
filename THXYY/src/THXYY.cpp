#include "THXYY.h"
#include "Scene\Title\Title.h"
#include "resource.h"

THXYY::THXYY()
{
	engine = nullptr;
}

THXYY::~THXYY()
{
	TH_SAFE_RELEASE(engine);
}

int THXYY::CreateGame(int width, int height, bool fullScreen)
{
	auto exceptionManager = ExceptionManager::GetInstance();

	if (TH_FAILED(Game::CreateGame(width, height, fullScreen, "THXYY", IDI_THXYY, IDI_SMALL)))
	{
		return -1;
	}

	engine = STGEngine::Create();
	if (engine == nullptr)
	{
		return -1;
	}
	engine->Retain();

	auto stgResources = STGResources::GetInstance();
	if (!stgResources->LoadSounds())
	{
		return -1;
	}

	Title* title = new Title();
	SetScene(title);

	return TH_SUCCESS;
}

void THXYY::OnShutdown()
{
	TH_SAFE_RELEASE(engine);

	Game::OnShutdown();
}