#include "SelectScene.h"
#include "SelectTitle.h"
#include "RankSelectMenu.h"
#include "../Title/Title.h"

static const int FADE_TIME = 24;
static const int OFFSET = 60;
static const int DELAY_TIME = 150;

SelectScene::SelectScene()
{
	auto assetManager = AssetManager::GetInstance();
	this->texBackground = assetManager->CreateTextureFromFile("res/menu/background.jpg");
	this->texBackground->Retain();

	SelectTitle::tex = assetManager->CreateTextureFromFile("res/menu/select.png");
	SelectTitle::tex->Retain();

	Layer* bgrLayer = new Layer();
	AddLayer(bgrLayer);

	Sprite* background = new Sprite();
	background->SetTexture(this->texBackground);
	background->SetPosition(Vector3f(320, 240, 0));
	TweenSequence* sequence = new TweenSequence();
	sequence->AddTween(new Delay(DELAY_TIME));
	sequence->AddTween(new ColorTo(Vector3f(0.5f, 0.5f, 0.5f), 100, Tweener::SIMPLE));
	sequence->AddTween(new Delay(DELAY_TIME));
	sequence->AddTween(new ColorTo(Vector3f(1.0f, 1.0f, 1.0f), 100, Tweener::SIMPLE));
	sequence->SetLooped(true);
	background->AddTween(sequence);
	bgrLayer->AddChild(background);

	this->uiLayer = new Layer();
	AddLayer(this->uiLayer);

	ShowRank();
}

SelectScene::~SelectScene()
{
	TH_SAFE_RELEASE(this->texBackground);
	TH_SAFE_RELEASE(SelectTitle::tex);
}

void SelectScene::ShowRank()
{
	this->title = new SelectTitle();
	this->title->SetType(SelectTitle::RANK_SELECT);
	this->title->SetPosition(Vector3f(480 + OFFSET, 416, 5));
	title->SetAlpha(0.0f);
	this->title->AddTween(new MoveTo(Vector3f(480, 416, 5), FADE_TIME, Tweener::SIMPLE));
	this->title->AddTween(new FadeTo(1.0f, FADE_TIME, Tweener::SIMPLE));
	this->uiLayer->AddChild(this->title);

	this->rankSelectMenu = new RankSelectMenu();
	AddLayer(this->rankSelectMenu);
}

void SelectScene::Back()
{
	this->title->AddTween(new MoveTo(Vector3f(480 + OFFSET, 416, 5), FADE_TIME, Tweener::SIMPLE));
	this->title->AddTween(new FadeOut(FADE_TIME, Tweener::SIMPLE));
	
	FrameTimer* timer = new FrameTimer();
	timer->SetFrame(FADE_TIME);
	timer->run = []() {
		auto game = Game::GetInstance();
		game->LoadScene(new Title());
	};
	GetScheduler()->AddTimer(timer);
}