#ifndef THCOMMON_H
#define THCOMMON_H

#define WINDOWS

#define TH_SAFE_DELETE(obj)  {if(obj){delete obj; obj = NULL;}}
#define TH_D3D_RELEASE(obj)  {if(obj){obj->Release(); obj = NULL;}}

#ifdef WINDOWS
#define TH_CHAR                     TCHAR
#define TH_TEXT(string)             TEXT(string)
#endif

#define PI                          3.1415926f
#define ZERO(x)                  (fabs(x)<1e-5)

#define DIKEYDOWN(data,id) (data[id] & 0x80)

#define DSVOLUME_TO_DB(volume) ((DWORD)(-30*(100-volume)))

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmreg.h>
#include <mmsystem.h>

//C++ Headers
#include <iostream>
#include <fstream>
using namespace std;

//DirectX 9
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>

//local includes
#include "THEnemy.h"
#include "THBullet.h"

class THXYY;
class THEngine;

extern THXYY game;
extern THEngine* engine;

void THMessageBox(TH_CHAR* string);

void SetStandardTransform();
int CreateTexture(TCHAR *FilePath);
void DestroyTexture(int tex);
int CreateSound(TCHAR *FilePath);
void PlaySE(int sound);
void SpriteBegin();
void SpriteEnd();
void SpriteDraw(int tex, int srcL, int srcT, int srcR, int srcB, float x, float y, int z, float alpha = 1, int r = 255, int g = 255, int b = 255);

void SetTexture(int tex);

float GetPlayerX();
float GetPlayerY();
int GetPlayerPower();
void SetPlayerPower(int power);
float GetAngleToPlayer(float x, float y);

float GetSpeedAngle(float vx, float vy);

/*void SetPerspectiveProjection(float angle, float aspect, float znear, float zfar);
void SetCamera(float x, float y, float z, float xLook, float yLook, float zLook, float xUp, float yUp, float zUp);

int CreateVertexBuffer(int nSize);
void ReleaseVertexBuffer(int vertexbuffer);
void* LockVertexBuffer(int vertexbuffer, int nStart, int nSize);
void UnlockVertexBuffer(int vertexbuffer);
void SetVertexData(void *start, int offset, float x, float y, float z, float xn, float yn, float zn, float u, float v);
void DrawVertexBuffer(int vertexbuffer, int nStart, int nSize, BYTE vbDrawType);
void EnableLighting(bool lighting);*/

void CreateEnemy(THEnemy* enemy, int x, int y, int delay = 0);
void CreatePlayerBullet(THPlayerBullet *bullet, float x, float y);
void Shoot(float x, float y, float v, float angle, int bullet, int delay);
THBullet *CreateBullet(float x, float y, float v, float angle, int bullet, int delay);
void ShootBullet(THBullet *bullet);
void DropItem(float x, float y, int item);

void AddRenderObject(RenderObject *renderobject);

int Random(int a, int b);

#endif