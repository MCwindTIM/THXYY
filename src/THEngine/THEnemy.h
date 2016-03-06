#ifndef THENEMY_H
#define THENEMY_H

#include "stdafx.h"
#include "RenderObject.h"

#define  ST1_01              1

#define FAIRY_BLUE1                       1
#define FAIRY_BLUE2                       2
#define FAIRY_RED1                        3
#define FAIRY_RED2                        4
#define FAIRY_GREEN1                      5
#define FAIRY_GREEN2                      6
#define FAIRY_YELLOW1                     7
#define FAIRY_YELLOW2                     8

#define FRAME_INTERVAL                    8

class THEnemy :public RenderObject{
protected:
	int life;
	UINT id;
	int delay;
	int damageRectW;   //判定矩形宽度
	int damageRectH;   //判定矩形高度
	int score;
	int frame;
	int frame_for_anm;
public:
	THEnemy();
	virtual void Draw();
	virtual void CommonDraw();
	virtual void CommonUpdate();
	virtual void Update();
	virtual void Destroy() = 0;
	virtual void CommonDestroy() = 0;
	virtual bool Hit(int x, int y, float radius);
	void Create(UINT id);
	inline void SetDelay(int delay){ this->delay = delay; }
	inline void SetLife(int life){ this->life = life; }
	inline void SetDamageRect(int w, int h){ damageRectW = w; damageRectH = h; }
	inline void SetScore(int score){ this->score = score; }
	inline int GetDamageRectW(){ return damageRectW; }
	inline int GetDamageRectH(){ return damageRectH; }
	inline int GetLife(){ return life; }
};

class Fairy :public THEnemy{
private:
	enum PREV_DIRECTION{
		LEFT,
		VERT,
		RIGHT,
		NONE
	};
	PREV_DIRECTION prev_direction;
	BYTE type;
public:
	Fairy();
	Fairy(BYTE type);
	virtual void Draw();
	virtual void CommonDestroy();
};

class RedFairy1 :public Fairy{
public:
	RedFairy1() :Fairy(FAIRY_RED1){}
};

class RedFairy2 :public Fairy{
public:
	RedFairy2() :Fairy(FAIRY_RED2){}
};

class GreenFairy1 :public Fairy{
public:
	GreenFairy1() :Fairy(FAIRY_GREEN1){}
};

class GreenFairy2 :public Fairy{
public:
	GreenFairy2() :Fairy(FAIRY_GREEN2){}
};

class BlueFairy1 :public Fairy{
public:
	BlueFairy1() :Fairy(FAIRY_BLUE1){}
};

class BlueFairy2 :public Fairy{
public:
	BlueFairy2() :Fairy(FAIRY_BLUE2){}
};

class YellowFairy1 :public Fairy{
public:
	YellowFairy1() :Fairy(FAIRY_YELLOW1){}
};

class YellowFairy2 :public Fairy{
public:
	YellowFairy2() :Fairy(FAIRY_YELLOW2){}
};

class ButterFly :public THEnemy{
private:
	enum PREV_DIRECTION{
		LEFT,
		VERT,
		RIGHT,
		NONE
	};
	PREV_DIRECTION prev_direction;
public:
	ButterFly();
	virtual void Draw();
	virtual void CommonDestroy();
};

#endif