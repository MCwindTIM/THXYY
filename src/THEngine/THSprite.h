#ifndef THSPRITE_H
#define THSPRITE_H

#include "THCommon.h"
#include "stdlib.h"
using namespace std;

#define MAX_SPRITE_ITEM         2000

struct THSpriteVertex{
	float x, y, z;
	float u, v;
	THSpriteVertex(){}
	THSpriteVertex(float x,float y,float z,float u,float v) :x(x),y(y),z(z),u(u),v(v){}
};

struct THSpriteDrawData{
	int tex;
	int srcL, srcT, srcR, srcB;
	float x, y;
	int z;
	float alpha;
	int r, g, b;
	D3DXMATRIX transform;
	int index;
};

class THSprite{
private:
	D3DXMATRIX _matrix;
	THEngine* _engine;
	IDirect3DVertexBuffer9* _vb;
	ID3DXEffect* _effect;
	THSpriteDrawData _renderlist[MAX_SPRITE_ITEM];
	int listTop;
public:
	THSprite();
	virtual ~THSprite();
	int Create(THEngine* engine);
	void SetTransform(D3DXMATRIX* matrix);
	void GetTransform(D3DXMATRIX* matrix);
	void Begin();
	void End();
	void Draw(int tex, int srcL, int srcT, int srcR, int srcB, float x, float y, int z,
		float alpha = 1.0f, int r = 255, int g = 255, int b = 255);
};

#endif