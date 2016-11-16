#include "Stage01.h"
#include "../Enemy/Stage01/Enemy01_001.h"

Texture* Stage01::texRoad = nullptr;

Stage01::Stage01()
{

}

Stage01::~Stage01()
{
	auto assetManager = AssetManager::GetInstance();

	assetManager->DestroyTexture(texRoad);

	TH_SAFE_RELEASE(house);
}

void Stage01::Update()
{
	Stage::Update();

	auto engine = STGEngine::GetInstance();

	frame++;

	if (frame == 1)
	{
		Enemy01_001* enemy = new Enemy01_001();
		enemy->SetPosition(-30, 420);
		enemy->AddTween(new MoveTo(Vector3f(192, 280,enemy->GetPosition().z),180,Tweener::EASE_OUT));
		engine->AddEnemy(enemy);
	}
}

void Stage01::OnLoad()
{
	auto assetManager = AssetManager::GetInstance();
	auto engine = STGEngine::GetInstance();

	texRoad = assetManager->CreateTextureFromFile("res/background/stage01/road.jpg", true);
	house = Mesh::CreateMeshFromFile("res/model/house/house.x");
	if (house == nullptr)
	{
		THMessageBox(ExceptionManager::GetInstance()->GetException()->GetInfo());
	}
	house->Retain();

	SetupCamera();
	SetupFog();
	InitBackgroundObjects();
}

void Stage01::UpdateBackground()
{
	Stage::UpdateBackground();

	auto engine = STGEngine::GetInstance();
	auto camera = engine->GetBackgroundCamera();

	Vector3f pos = camera->GetPosition();
	float z = pos.z;
	z += 2;
	if (z > 2000)
	{
		z -= 2000;
	}
	pos.z = z;

	camera->SetPosition(pos);
}

void Stage01::SetupCamera()
{
	auto engine = STGEngine::GetInstance();

	Camera3D* camera = new Camera3D();
	camera->SetPosition(Vector3f(600, 500, 0));
	camera->SetUp(Vector3f(0, 1, 0));
	camera->SetLookAt(Vector3f(600, 500, 10000));
	engine->SetBackgroundCamera(camera);
}

void Stage01::SetupFog()
{
	auto scene = (GameScene*)(Game::GetInstance()->GetScene());
	auto backgroundLayer = scene->GetBackgroundLayer();

	backgroundLayer->EnableFog(true);

	Fog fog;
	fog.fogColor = Vector4f(0, 0, 0, 0);
	fog.fogStart = 200;
	fog.fogEnd = 1500;
	backgroundLayer->SetFog(fog);
}

void Stage01::InitBackgroundObjects()
{
	auto engine = STGEngine::GetInstance();

	Mesh* road = new Mesh();
	road->InitVertexBuffer(4);

	MeshVertex meshVertices[4] = {
		{ -10000, 0, -10000, 0, 1, 0, -100, -100 },
		{ 10000, 0, -10000, 0, 1, 0, 100, -100 },
		{ -10000, 0, 10000, 0, 1, 0, -100, 100 },
		{ 10000, 0, 10000, 0, 1, 0, 100, 100 }
	};

	road->SetVertexData(meshVertices);
	road->SetPrimitiveType(Mesh::TRIANGLE_STRIP);

	Material roadMaterial;
	roadMaterial.texture = texRoad;

	road->SetMaterial(roadMaterial);

	engine->AddBackgroundObject(road);

	Mesh* houseLeft = (Mesh*)house->Clone();
	houseLeft->SetPosition(Vector3f(0, 395, 1000));
	engine->AddBackgroundObject(houseLeft);
}