#include "THLayer.h"
#include "THGame.h"

using namespace THEngine;

Layer::Layer()
{
	this->left = 0;
	this->top = 0;
	this->width = Game::GetInstance()->GetWidth();
	this->height = Game::GetInstance()->GetHeight();

	this->camera = new Camera2D;
	camera->Retain();
	((Camera2D*)camera)->SetViewRect(Rect(0, width, height, 0));
}

Layer::Layer(int left, int top, int width, int height)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;

	this->camera = new Camera2D;
	camera->Retain();
	((Camera2D*)camera)->SetViewRect(Rect(0, width, height, 0));
}

Layer::~Layer()
{
	TH_SAFE_RELEASE(camera);
}

void Layer::AddChild(GameObject* obj)
{
	rootNode.AddChild(obj);
}

void Layer::SetCamera(Camera* camera)
{
	TH_SAFE_RELEASE(this->camera);
	this->camera = camera;
	this->camera->Retain();
}

void Layer::Update()
{
	EngineObject::Update();

	rootNode.Update();
}

void Layer::Draw()
{
	Application::GetInstance()->SetViewport(left, top, width, height);

	Camera2D* camera2D;
	if (camera2D = dynamic_cast<Camera2D*>(camera)){
		Rect rect = camera2D->GetViewRect();
		Application::GetInstance()->SetOrtho(rect.left, rect.bottom, rect.Width(), -rect.Height(), 0, TH_MAX_Z);
	}

	rootNode.Visit();

	Game::GetInstance()->Render();

	Application::GetInstance()->ClearDepthBuffer();
}

void Layer::DestroyObjectImmediately(GameObject* obj)
{
	obj->OnDestroy();
	rootNode.RemoveChild(obj);
}

void Layer::OnActivate()
{
	activated = true;
}

void Layer::OnDestroy()
{
	rootNode.OnDestroy();
}