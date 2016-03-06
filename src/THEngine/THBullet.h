#ifndef THBULLET_H
#define THBULLET_H

#include "THCommon.h"
#include "RenderObject.h"
#include "THEvent.h"
#include <list>
using namespace std;
 
#define TH_MAX_BULLET_EVENT                                  10
#define TH_MAX_BULLET_EVENT_HANDLER                          100

/**************子弹类型****************/
//小玉
#define SMALLJADE_RED                                        1
#define SMALLJADE_PURPLE                                     2
#define SMALLJADE_BLUE                                       3
#define SMALLJADE_TEAL                                       4
#define SMALLJADE_GREEN                                      5
#define SMALLJADE_YELLOW                                     6
#define SMALLJADE_ORANGE                                     7
#define SMALLJADE_GREY                                       8

//鳞弹
#define SCALE_RED                                        21
#define SCALE_PURPLE                                     22
#define SCALE_BLUE                                       23
#define SCALE_TEAL                                       24
#define SCALE_GREEN                                      25
#define SCALE_YELLOW                                     26
#define SCALE_ORANGE                                     27
#define SCALE_GREY                                       28

class BulletEventHandler;

class THBullet :public RenderObject{
protected:
	int type;
	int delay;
	int frame;
	int fog;
	bool bFog;                          //雾化效果
	bool bDeleteEffect;             //消弹效果
	bool bHighlight;                  //高光效果
	bool bShade;                      //拖影效果
	bool bDeleteOutOfScreen;  //出屏即消
	bool bDetermination;         //是否有中弹判定
	THBulletEvent* events[TH_MAX_BULLET_EVENT];
	BulletEventHandler* eventHandlers[TH_MAX_BULLET_EVENT_HANDLER];
	int eventNum;
	int eventHandlerNum;
protected:
	void HandleEvent();
	BulletEventHandler* CreateBulletEventHandler(THBulletEvent* e);
public:
	THBullet(int type);
	virtual ~THBullet();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void CommonUpdate();
	virtual void CommonDraw();
	virtual bool Hit(float x, float y, float radius);
	inline void EnableDetermination(){ bDetermination = true; }
	inline void DisableDetermination(){ bDetermination = false; }
	inline bool HasDetermination(){ return bDetermination; }
	inline void SetFog(int fog){ this->fog = fog; }
	inline int GetFog(){ return fog; }
	inline void SetDelay(int delay){ this->delay = delay; }
	void SetType(int type);
	int AddEvent(THBulletEvent* e);
	friend class BulletEventHandler;
};

class BulletEventHandler{
public:
	THBullet* bullet;
	BYTE attributeType;
	BYTE changeManner;
	float deltaTotal;
	float deltaPerFrame;
	int totalFrame;
	int leftFrame;
public:
	BulletEventHandler();
	~BulletEventHandler();
	int Handle();
};

class THPlayerBullet :public RenderObject{
protected:
	UINT damage;
	bool  bAttackOnce;
public:
	THPlayerBullet();
	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual void CommonUpdate();
	virtual void CommonDraw();
	virtual bool Hit(float l, float t, float r, float b) = 0;
	inline void SetDamage(UINT damage){ this->damage = damage; }
	inline void SetAttackOnce(bool attack_once){ bAttackOnce = attack_once; }
	inline int GetDamage(){ return damage; }
	inline bool AttackOnce(){ return bAttackOnce; }
};


#endif