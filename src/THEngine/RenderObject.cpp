#include "stdafx.h"
#include "RenderObject.h"
#include "math.h"
#include "THCommon.h"
#include "Engine_Core.h"

RenderObject::RenderObject()
{
	texture = -1;
	alpha = 1;
	EnableAutoDelete();
	SetRange(0, 384, 0, 448);
	bNeedDelete = false;
	ax = ay = 0;
	anglespeed = 0;
	vmin = -99999;
	vmax = 99999;
	anglemin = -99999;
	anglemax = 99999;
	av = 0;
	velocity = 0;
	angle = 0;
	x = y = 0;
	updatetype = UPDATETYPE_V_ANGLE;
}

RenderObject::~RenderObject()
{

}

void RenderObject::SetRange(int xmin, int xmax, int ymin, int ymax){
	this->xmin = xmin;
	this->xmax = xmax;
	this->ymin = ymin;
	this->ymax = ymax;
}

void RenderObject::SetTexture(int tex)
{
	this->texture = tex;
}

int RenderObject::GetTexture()
{
	return this->texture;
}

void RenderObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void RenderObject::SetVelocity(float velocity)
{
	this->velocity = velocity;
}

void RenderObject::SetDirection(int xdir, int ydir)
{
	this->xdir = xdir;
	this->ydir = ydir;
	CalStep();
}

void RenderObject::SetImgRect(int l, int t, int r, int b){
	imgRect.left = l;
	imgRect.right = r;
	imgRect.top = t;
	imgRect.bottom = b;
	imgWidth = r - l;
	imgHeight = b - t;
}

void RenderObject::SetRotation(float x, float y, float angle){
	D3DXMATRIX trans, temp;
	engine->_sprite->GetTransform(&trans);
	D3DXMatrixTranslation(&temp, -x, -y, 0);
	trans *= temp;
	D3DXMatrixRotationZ(&temp, angle / 180.0f * PI);
	trans *= temp;
	D3DXMatrixTranslation(&temp, x, y, 0);
	trans *= temp;
	engine->_sprite->SetTransform(&trans);
}

void RenderObject::SetScale(float x, float y, float sx, float sy){
	D3DXMATRIX trans, temp;
	engine->_sprite->GetTransform(&trans);
	D3DXMatrixTranslation(&temp, -x, -y, 0);
	trans *= temp;
	D3DXMatrixScaling(&temp, sx, sy, 1);
	trans *= temp;
	D3DXMatrixTranslation(&temp, x, y, 0);
	trans *= temp;
	engine->_sprite->SetTransform(&trans);
}

void RenderObject::SetReversalX(float x){
	D3DXMATRIX trans, temp;
	engine->_sprite->GetTransform(&trans);
	D3DXMatrixTranslation(&temp, -x, 0, 0);
	trans *= temp;
	D3DXMatrixIdentity(&temp);
	temp._11 = -1;
	trans *= temp;
	D3DXMatrixTranslation(&temp, x, 0, 0);
	trans *= temp;
	engine->_sprite->SetTransform(&trans);
}

void RenderObject::SetReversalY(float y){
	D3DXMATRIX trans, temp;
	engine->_sprite->GetTransform(&trans);
	D3DXMatrixTranslation(&temp, 0, -y, 0);
	trans *= temp;
	D3DXMatrixIdentity(&temp);
	temp._22 = -1;
	trans *= temp;
	D3DXMatrixTranslation(&temp, 0, y, 0);
	trans *= temp;
	engine->_sprite->SetTransform(&trans);
}

void RenderObject::SetUpdateType(BYTE type){
	if ((type == UPDATETYPE_XY) && (this->updatetype == UPDATETYPE_V_ANGLE)){
		vx = velocity * cos(angle);
		vy = velocity * sin(angle);
		ax = ay = 0;
	}
	else if ((type == UPDATETYPE_V_ANGLE) && (this->updatetype == UPDATETYPE_XY)){
		velocity = sqrt(vx*vx + vy*vy);
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
	}
	this->updatetype = type;
}

void RenderObject::ClearTransform()
{
	SetStandardTransform();
}

void RenderObject::DrawImg(float x, float y, int z, DWORD dwFlag, int r, int g, int b)
{
	switch (dwFlag){
	case DRAW_CENTERED:
		SpriteDraw(this->texture, imgRect.left, imgRect.top, imgRect.right, imgRect.bottom,
			x - imgWidth / 2, y - imgHeight / 2, z, alpha, r, g, b);
		break;
	case DRAW_LEFTTOP:
		SpriteDraw(this->texture, imgRect.left, imgRect.top, imgRect.right, imgRect.bottom,
			x, y, z, alpha, r, g, b);
		break;
	default:
		break;
	}
}

void RenderObject::MoveTo(float xdest, float ydest)
{
	this->xdir = xdest - x;
	this->ydir = ydest - y;
	CalStep();
}

void RenderObject::CalStep()
{
	x_step = (float)velocity * xdir / sqrt((float)xdir*xdir + ydir*ydir);
	y_step = (float)velocity * ydir / sqrt((float)xdir*xdir + ydir*ydir);
}

void RenderObject::UpdatePosition()
{
	if (updatetype == UPDATETYPE_V_ANGLE){
		velocity += av;
		angle += anglespeed;
		if (velocity > vmax){
			velocity = vmax;
		}
		if (velocity < vmin){
			velocity = vmin;
		}
		if (angle > anglemax){
			angle = anglemax;
		}
		if (angle < anglemin){
			angle = anglemin;
		}
		x += (velocity)*cos(angle / 180.0f * PI);
		y += (velocity)*sin(angle / 180.0f * PI);
	}
	else if (updatetype == UPDATETYPE_XY){
		vx += (float)ax;
		vy += (float)ay;
		if (vx < vxmin){
			vx = vxmin;
		}
		if (vx > vxmax){
			vx = vxmax;
		}
		if (vy < vymin){
			vy = vymin;
		}
		if (vy > vymax){
			vy = vymax;
		}
		x += vx;
		y += vy;
	}
	else if (updatetype == UPDATETYPE_CS){
		ax = av * cos(acangle / 180.0f * PI);
		ay = av * sin(acangle / 180.0f * PI);
		vx = velocity * cos(angle / 180.0f * PI);
		vy = velocity * sin(angle / 180.0f * PI);
		vx += ax;
		vy += ay;
		velocity = sqrt(vx*vx + vy*vy);
		angle = GetSpeedAngle(vx, vy);
		x += vx;
		y += vy;
	}
}

bool RenderObject::NeedAutoDelete()
{
	if (bAutoDelete){
		if (x<xmin || x>xmax || y<ymin || y>ymax){
			return true;
		}
		if (bNeedDelete){
			return true;
		}
	}
	return false;
}