#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "stdafx.h"

#define UPDATETYPE_V_ANGLE             1
#define UPDATETYPE_XY                  2
#define UPDATETYPE_CS                  3


#define DRAW_CENTERED                  1
#define DRAW_LEFTTOP                   2

class Engine;

class RenderObject{
protected:
	float x, y;
	float angle;
	float anglespeed;
	int xmin, xmax, ymin, ymax;    //坐标范围（超出此范围即删除该对象）
	float velocity;             //速度
	float vx, vy;
	float av;                    //加速度 
	float acangle;            //加速度方向
	float ax, ay;                   //加速度
	float vmax, vmin;               //最大速度和最小速度
	float anglemax, anglemin;       //最大角度和最小角度
	float vxmin, vxmax, vymin, vymax; //最大速度
	float xdir, ydir;               //方向向量
	float x_step, y_step;         //每帧位移量
	int texture;
	RECT imgRect;
	int imgWidth;
	int imgHeight;
	float alpha;                //透明度
	bool bAutoDelete;           //是否启用自动删除
	bool bNeedDelete;           //是否需要删除
	BYTE updatetype;            //更新方式（XY坐标方式或速度-角度方式）
public:
	RenderObject();
	virtual ~RenderObject();
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void CommonUpdate(){
		Update();
	}
	virtual void CommonDraw(){
		Draw();
	}
	void DrawImg(float x, float y, int z, DWORD dwFlag, int r = 255, int g = 255, int b = 255);
	void SetRange(int xmin, int xmax, int ymin, int ymax);
	inline void EnableAutoDelete(){ bAutoDelete = true; }
	inline void DisableAutoDelete(){ bAutoDelete = false; }
	void SetTexture(int tex);
	inline int GetTexture();
	void SetDirection(int xdir, int ydir);
	void SetVelocity(float velocity);
	inline void SetVelocity_XY(float vx, float vy){
		this->vx = vx;
		this->vy = vy;
	}
	void SetPosition(float x, float y);
	void SetImgRect(int l, int t, int r, int b);
	void SetRotation(float x, float y, float angle);
	void SetScale(float x, float y, float sx, float sy);
	void SetReversalX(float x);
	void SetReversalY(float y);
	inline void SetAngle(float angle){ this->angle = angle; }
	inline void SetAngleSpeed(float anglespeed){ this->anglespeed = anglespeed; }
	inline void SetAlpha(float alpha){ this->alpha = alpha; }
	inline void SetAcceleration(float a){ this->av = a; }
	inline void SetAcAngle(float acangle){ this->acangle = acangle; }
	inline void SetAcceleration_XY(float ax, float ay){ this->ax = ax; this->ay = ay; }
	inline void SetVelocityRange(float vmin, float vmax){
		this->vmin = vmin;
		this->vmax = vmax;
	}
	inline void SetVelocityRange_XY(float vxmin, float vxmax, float vymin, float vymax){
		this->vxmin = vxmin;
		this->vxmax = vxmax;
		this->vymin = vymin;
		this->vymax = vymax;
	}
	void SetUpdateType(BYTE type);
	inline float GetX(){ return x; }
	inline float GetY(){ return y; }
	void ClearTransform();
	void MoveTo(float xdest, float ydest);
	void CalStep();
	void UpdatePosition();
	bool NeedAutoDelete();
	inline void MarkDelete(){ bNeedDelete = true; }

	friend class Engine;
};

#endif