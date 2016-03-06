#include "stdafx.h"
#include "THSprite.h"
#include "Engine_Core.h"

int THSpriteCmp1(const void *a, const void *b){
	return ((THSpriteDrawData*)a)->z < ((THSpriteDrawData*)b)->z;
}

int THSpriteCmp2(const void *a, const void *b){
	return ((THSpriteDrawData*)a)->index >((THSpriteDrawData*)b)->index;
}

THSprite::THSprite()
{
	_vb = NULL;
	_effect = NULL;
	listTop = 0;
}

THSprite::~THSprite()
{
	TH_D3D_RELEASE(_vb);
	TH_D3D_RELEASE(_effect);
}

int THSprite::Create(THEngine* engine)
{
	_engine = engine;
	if (FAILED(_engine->_device->CreateVertexBuffer(4 * sizeof(THSpriteVertex), 0,
		D3DFVF_XYZ | D3DFVF_TEX1 , D3DPOOL_MANAGED, &_vb, NULL)))
	{
		TH_D3D_RELEASE(_vb);
		return -1;
	}
	if (FAILED(_engine->LoadEffect(TEXT("fx/sprite.fx"), &_effect))){
		TH_D3D_RELEASE(_vb);
		TH_D3D_RELEASE(_effect);
		return -1;
	}
	_effect->SetTechnique("Sprite");

	listTop = 0;
	return 0;
}

void THSprite::Begin()
{
	UINT nPasses;
	_engine->_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	_effect->Begin(&nPasses, 0);
}

void THSprite::End()
{
	qsort(_renderlist, listTop, sizeof(THSpriteDrawData), THSpriteCmp1);
	for (int i = 0; i < listTop; i++) {
		THSpriteDrawData data = _renderlist[i];
		//Get texture size
		IDirect3DTexture9* texture = _engine->_texList[data.tex];
		D3DSURFACE_DESC desc;
		texture->GetLevelDesc(0, &desc);
		const int texWidth = desc.Width;
		const int texHeight = desc.Height;
		const int width = data.srcR - data.srcL;
		const int height = data.srcB - data.srcT;

		//Transform to texture coordinates
		float left = data.srcL * 1.0f / texWidth;
		float top = data.srcT * 1.0f / texHeight;
		float right = data.srcR * 1.0f / texWidth;
		float bottom = data.srcB * 1.0f / texHeight;

		THSpriteVertex* vertices;
		_vb->Lock(0, 0, (void**)&vertices, D3DLOCK_DISCARD);
		vertices[0] = THSpriteVertex(data.x, data.y, data.z, left, top);
		vertices[1] = THSpriteVertex(data.x + width, data.y, data.z, right, top);
		vertices[2] = THSpriteVertex(data.x, data.y + height, data.z, left, bottom);
		vertices[3] = THSpriteVertex(data.x + width, data.y + height, data.z, right, bottom);
		_vb->Unlock();

		float argb[4];
		argb[0] = data.alpha;
		argb[1] = data.r * (1.0f / 255);
		argb[2] = data.g * (1.0f / 255);
		argb[3] = data.b * (1.0f / 255);

		_effect->SetFloatArray("argb", argb, 4);
		_effect->SetTexture("tex", texture);
		_effect->SetInt("texWidth", texWidth);
		_effect->SetInt("texHeight", texHeight);

		_engine->_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		_engine->_device->SetTransform(D3DTS_WORLD, &data.transform);
		_engine->_device->SetStreamSource(0, _vb, 0, sizeof(THSpriteVertex));
		_effect->BeginPass(0);
		_engine->_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		_effect->EndPass();
	}
	listTop = 0;
	_effect->End();
	D3DXMATRIX dm;
	D3DXMatrixIdentity(&dm);
	_engine->_device->SetTransform(D3DTS_WORLD, &dm);
}

void THSprite::SetTransform(D3DXMATRIX* matrix)
{
	_matrix = *matrix;
}

void THSprite::GetTransform(D3DXMATRIX* matrix)
{
	*matrix = _matrix;
}

void THSprite::Draw(int tex, int srcL, int srcT, int srcR, int srcB, float x, float y, int z,
	float alpha, int r, int g, int b)
{
	THSpriteDrawData data;
	data.tex = tex;
	data.srcL = srcL;
	data.srcT = srcT;
	data.srcR = srcR;
	data.srcB = srcB;
	data.x = x;
	data.y = y;
	data.z = z;
	data.alpha = alpha;
	data.r = r;
	data.g = g;
	data.b = b;
	data.transform = _matrix;
	data.index = listTop;

	_renderlist[listTop++] = data;
}