#include "stdafx.h"
#include "THCommon.h"
#include "THEngine.h"
#include "Effect\THFog.h"
#include "THSound\CWaveFile.h"

void THMessageBox(TH_CHAR* string)
{
#ifdef WINDOWS
	MessageBox(NULL, string, NULL, MB_OK);
#endif
}

void SetStandardTransform()
{
	D3DXMATRIX dm;
	D3DXMatrixIdentity(&dm);
	engine->_sprite->SetTransform(&dm);
}

int CreateTexture(TCHAR *FilePath){
	int i;
	for (i = 0; i < TH_MAX_TEXTURE; i++) {
		if (engine->_texList[i] == NULL){
			break;
		}
	}
	if (i == TH_MAX_TEXTURE){
		return -1;
	}
	if (FAILED(D3DXCreateTextureFromFile(engine->_device, FilePath, &engine->_texList[i]))){
		TCHAR str[50];
		swprintf(str, sizeof(str), L"Cannot load file : %s ", FilePath);
		THMessageBox(str);
		return -1;
	}
	return i;
}

void DestroyTexture(int tex){
	TH_D3D_RELEASE(engine->_texList[tex])
}

int CreateSound(TCHAR *FilePath){
	int i;
	for (i = 0; i < TH_MAX_SOUND; i++) {
		if (engine->_soundBuffer[i] == NULL){
			break;
		}
	}
	if (i == TH_MAX_SOUND){
		return -1;
	}

	CWaveFile wave;
	WAVEFORMATEX wf;
	if (FAILED(wave.Open(FilePath, &wf, WAVEFILE_READ))){
		TCHAR str[50];
		swprintf(str, sizeof(str), TEXT("Cannot load file:%s"), FilePath);
		THMessageBox(str);
		return -2;
	}

	DSBUFFERDESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.dwBufferBytes = wave.GetSize();
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.lpwfxFormat = wave.GetFormat();
	desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME;

	if (FAILED(engine->_sound->CreateSoundBuffer(&desc, &engine->_soundBuffer[i], NULL))){
		TCHAR str[50];
		swprintf(str, sizeof(str), TEXT("Cannot create sound buffer while loading file:%s"), FilePath);
		THMessageBox(str);
		return -3;
	}
	IDirectSoundBuffer* sound = engine->_soundBuffer[i];
	VOID* lockedBuffer;
	DWORD lockedBufferSize;
	if (FAILED(sound->Lock(0, wave.GetSize(), &lockedBuffer, &lockedBufferSize, NULL, NULL, 0))){
		TCHAR str[50];
		swprintf(str, sizeof(str), TEXT("Cannot lock sound buffer while loading file:%s"), FilePath);
		THMessageBox(str);
		return -4;
	}
	DWORD readSize;
	if (FAILED(wave.Read((BYTE*)lockedBuffer, lockedBufferSize, &readSize))){
		TCHAR str[50];
		swprintf(str, sizeof(str), TEXT("Cannot read sound data while loading file:%s"), FilePath);
		THMessageBox(str);
		return -5;
	}
	sound->SetVolume(DSVOLUME_TO_DB(40));
	return i;
}

void PlaySE(int sound){
	IDirectSoundBuffer* soundBuffer = engine->_soundBuffer[sound];
	DWORD status;
	soundBuffer->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING){
		soundBuffer->SetCurrentPosition(0);
	}
	soundBuffer->Play(0,0,0);
}

void SpriteBegin(){
	engine->_sprite->Begin();
}

void SpriteEnd(){
	engine->_sprite->End();
}

void SpriteDraw(int tex, int srcL, int srcT, int srcR, int srcB, float x, float y, int z, float alpha, int r, int g, int b){
	engine->_sprite->Draw(tex, srcL, srcT, srcR, srcB, x, y, z, alpha, r, g, b);
}

float GetPlayerX()
{
	return engine->_player->GetX();
}

float GetPlayerY()
{
	return engine->_player->GetY();
}

int GetPlayerPower()
{
	return engine->_player->GetPower();
}

float GetAngleToPlayer(float x, float y){
	float xdir = engine->_player->GetX() - x;
	float ydir = engine->_player->GetY() - y;
	if (xdir>0){
		return atan((float)ydir / xdir) * 180.0f / PI;
	}
	if (xdir<0){
		return atan((float)ydir / xdir) * 180.0f / PI + 180;
	}
	if (ydir>0){
		return 90;
	}
	if (ydir<0){
		return -90;
	}
	return 0;
}

float GetSpeedAngle(float vx, float vy){
	float angle;
	if (vx == 0){
		if (vy > 0){
			angle = 90;
		}
		else if (vy < 0){
			angle = -90;
		}
		else{
			angle = 0;
		}
	}
	else{
		angle = atan(vy / vx) * 180.0f / PI;
	}
	if (vx < 0){
		angle = angle + 180;
	}
	return angle;
}

void SetPlayerPower(int power){
	engine->_player->SetPower(power);
}

void CreateEnemy(THEnemy *enemy, int x, int y, int delay)
{
	enemy->SetPosition(x, y);
	enemy->SetDelay(delay);
	engine->_enemylist->Add(enemy);
}

void CreatePlayerBullet(THPlayerBullet *bullet, float x, float y)
{
	bullet->SetPosition(x, y);
	engine->_playerbulletlist->Add(bullet);
}

void Shoot(float x, float y, float v, float angle, int bullet, int delay){
	THBullet *pBul;
	PlaySE(engine->_soundShoot1);
	pBul = new THBullet(bullet);
	pBul->SetPosition(x, y);
	pBul->SetAngle(angle);
	pBul->SetVelocity(v);
	pBul->SetDelay(delay);
	engine->_bulletlist->Add(pBul);
	THBulletFog *fog = new THBulletFog(pBul->GetFog());
	fog->SetPosition(x, y);
	AddRenderObject(fog);
}

THBullet *CreateBullet(float x, float y, float v, float angle, int bullet, int delay){
	THBullet *pBul = NULL;
	pBul = new THBullet(bullet);
	pBul->SetPosition(x, y);
	pBul->SetAngle(angle);
	pBul->SetVelocity(v);
	pBul->SetDelay(delay);
	return pBul;
}

void ShootBullet(THBullet *bullet){
	PlaySE(engine->_soundShoot1);
	engine->_bulletlist->Add(bullet);
	THBulletFog *fog = new THBulletFog(bullet->GetFog());
	fog->SetPosition(bullet->GetX(), bullet->GetY());
	AddRenderObject(fog);
}

void DropItem(float x, float y, int item){
	PowerItemSmall* pItem;
	switch (item){
	case ITEM_POWER_SMALL:
		pItem = new PowerItemSmall;
		pItem->SetPosition(x, y);
		engine->_itemlist->Add(pItem);
		break;
	default:
		break;
	}
}

void SetTexture(int tex){
	engine->_device->SetTexture(0, engine->_texList[tex]);
}

void AddRenderObject(RenderObject *renderobject){
	engine->_renderlist->Add(renderobject);
}

/*void SetPerspectiveProjection(float angle, float aspect, float znear, float zfar){
	D3DXMATRIX dm;
	D3DXMatrixPerspectiveFovLH(&dm, angle, aspect, znear, zfar);
	game->m_engine->m_device->SetTransform(D3DTS_PROJECTION, &dm);
}

void SetCamera(float x, float y, float z, float xLook, float yLook, float zLook, float xUp, float yUp, float zUp){
	D3DXMATRIX dm;
	D3DXMatrixLookAtLH(&dm, &D3DXVECTOR3(x, y, z), &D3DXVECTOR3(xLook, yLook, zLook), &D3DXVECTOR3(xUp, yUp, zUp));
	game->m_engine->m_device->SetTransform(D3DTS_VIEW, &dm);
}

int CreateVertexBuffer(int nSize)
{
	Engine *engine = game->m_engine;
	int i;
	for (i = 0; i<MAX_VERTEX_BUFFER; i++){
		if (engine->m_vbList[i] == NULL){
			break;
		}
	}
	if (i == MAX_VERTEX_BUFFER){
		return -1;
	}
	if (FAILED(engine->m_device->CreateVertexBuffer(nSize*sizeof(Vertex),
		0,
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
		D3DPOOL_MANAGED,
		&engine->m_vbList[i],
		NULL))){
		CString str;
		str = TEXT("Fail to Create VertexBuffer!");
		AfxMessageBox(str);
		return -1;
	}
	return i;
}

void ReleaseVertexBuffer(int vertexbuffer){
	D3D_RELEASE(game->m_engine->m_vbList[vertexbuffer])
}

void* LockVertexBuffer(int vertexbuffer, int nStart, int nSize){
	void *vertices;
	game->m_engine->m_vbList[vertexbuffer]->Lock(0, 0, (void **)&vertices, 0);
	return vertices;
}

void UnlockVertexBuffer(int vertexbuffer){
	game->m_engine->m_vbList[vertexbuffer]->Unlock();
}

void SetVertexData(void *start, int offset, float x, float y, float z, float xn, float yn, float zn, float u, float v){
	Vertex *vertices = (Vertex*)start;
	vertices[offset] = Vertex(x, y, z, xn, yn, zn, u, v);
}

void DrawVertexBuffer(int vertexbuffer, int nStart, int nSize, BYTE vbDrawType){
	game->m_engine->m_device->SetStreamSource(0, game->m_engine->m_vbList[vertexbuffer], 0, sizeof(Vertex));
	game->m_engine->m_device->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);
	switch (vbDrawType){
	case VBDRAW_TRIANGLELIST:
		game->m_engine->m_device->DrawPrimitive(D3DPT_TRIANGLELIST, nStart, nSize);
		break;
	case VBDRAW_TRIANGLEFAN:
		game->m_engine->m_device->DrawPrimitive(D3DPT_TRIANGLEFAN, nStart, nSize);
		break;
	case VBDRAW_TRIANGLESTRIP:
		game->m_engine->m_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, nStart, nSize);
		break;
	}
}

void EnableLighting(bool lighting){
	game->m_engine->m_device->SetRenderState(D3DRS_LIGHTING, lighting);
}*/

int Random(int a, int b){
	int temp = rand();
	temp %= b - a + 1;
	return (int)temp + a;
}