#include "stdafx.h"
#include "Stage1.h"
#include "Enemy1.h"

Stage1::Stage1()
{
	Init();
}

Stage1::~Stage1()
{
	//DestroyTexture(texFloor);
	//ReleaseVertexBuffer(vbFloor);
}

void Stage1::Init()
{
	this->frame = 0;

	/*vbFloor = CreateVertexBuffer(4);
	texFloor = CreateTexture(TEXT("res/magic.jpg"));

	void * buffer = LockVertexBuffer(vbFloor, 0, 4);
	SetVertexData(buffer, 0, -10, 0, -10, 0, 1, 0, 0, 0);
	SetVertexData(buffer, 1, -10, 0, 10, 0, 1, 0, 0, 2);
	SetVertexData(buffer, 2, 10, 0, -10, 0, 1, 0, 2, 0);
	SetVertexData(buffer, 3, 10, 0, 10, 0, 1, 0, 2, 2);

	UnlockVertexBuffer(vbFloor);

	EnableLighting(false);*/

	int i;
	for (i = 0; i<10; i++){
		Enemy1_001 *e = new Enemy1_001;
		CreateEnemy(e, -16, 40, 100 + 20 * i);
		Enemy1_002 *e2 = new Enemy1_002;
		CreateEnemy(e2, 400, 40, 100 + 20 * i);
	}
	Enemy1_003 *e3 = new Enemy1_003;
	CreateEnemy(e3, 192, -32, 240);
	EnemyTest * e4 = new EnemyTest;
	CreateEnemy(e4, 192, -32, 600);
}

void Stage1::Update()
{

}

void Stage1::Draw()
{
	//game->m_engine->m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(1, 0, 0, 0), 1, 0);
	/*SetPerspectiveProjection(PI / 2, 6.0f / 7, 1, 1000);
	int temp = (frame + 1200) % 1800;
	temp -= 1200;
	float z = temp / 60.0;

	SetCamera(0, 2, z, 0, 2, z + 1, 0, 1, 0);*/

	/*D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_SPOT;
	light.Position = D3DXVECTOR3(0, 1, z);
	light.Direction = D3DXVECTOR3(0, 0, 1);
	light.Diffuse = D3DXCOLOR(1,1,1,1);
	light.Specular = D3DXCOLOR(1,1,1,1) * 0.6f;
	light.Ambient = D3DXCOLOR(0, 0, 0, 1);
	light.Range = 100;
	light.Falloff = 1;
	light.Attenuation0 = 1;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;
	light.Phi = D3DX_PI ;
	light.Theta = D3DX_PI / 2;

	game->m_engine->m_device->SetLight(0, &light);
	game->m_engine->m_device->LightEnable(0, true);

	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	mat.Specular = D3DXCOLOR(1, 1, 1, 1);
	mat.Ambient = D3DXCOLOR(1, 1, 1, 1);
	mat.Emissive = D3DXCOLOR(0, 0, 0, 0);
	mat.Power = 5;
	game->m_engine->m_device->SetMaterial(&mat);*/

	//SetTexture(texFloor);
	//DrawVertexBuffer(vbFloor, 0, 2, VBDRAW_TRIANGLESTRIP);
}