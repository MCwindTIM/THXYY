#include "Title.h"
#include "TitleMenu.h"

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
}

Title::~Title()
{
	AssetManager::GetInstance()->DestroyTexture(titleTex);
}