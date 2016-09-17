#include "Title.h"
#include "TitleMenu.h"
#include "../../STGCore/STGCore.h"

Title::Title()
{
	bgrLayer = new Layer();
	bgrLayer->SetOrder(100);
	
	titleTex = AssetManager::GetInstance()->CreateTextureFromFile("res/title/title.jpg");

	Sprite* background = new Sprite();
	background->SetTexture(titleTex);
	background->SetPivot(Vector2f(0.0f, 0.0f));
	bgrLayer->AddChild(background);
	this->AddLayer(bgrLayer);

	TitleMenu* titleMenu = new TitleMenu();
	titleMenu->SetOrder(50);
	this->AddLayer(titleMenu);

	blackLayer = new Layer();
	blackLayer->SetOrder(0);
	black = new Sprite();
	black->SetTexture(Global::GetInstance()->texBlack);
	black->SetPosition(Vector3f(0.0f, 0.0f, 1.0f));
	black->SetPivot(Vector2f(0.0f, 0.0f));
	black->AddTween(new FadeTo(0.0f, 80, Tweener::EASE_OUT));
	blackLayer->AddChild(black);
	AddLayer(blackLayer);

	particleLayer = new ParticleLayer();
	particleLayer->SetOrder(20);
	AddLayer(particleLayer);
}

Title::~Title()
{
	AssetManager::GetInstance()->DestroyTexture(titleTex);
}