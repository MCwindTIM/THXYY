#ifndef THEVENT_H
#define THEVENT_H

#include "stdafx.h"
#include "RenderObject.h"
#include <vector>
using namespace std;


#define EVENT_CREATION           1


#define CONDITION_FRAME          1
#define CONDITION_X              2
#define CONDITION_Y              3

#define RELATION_AND             1
#define RELATION_OR              2

#define COMPARISON_BIGGER        1
#define COMPARISON_EQUAL         2
#define COMPARISON_SMALLER       3

#define ATTRIBUTE_LIFE                                             1               //生命
#define ATTRIBUTE_TYPE                                             2              //类型
#define ATTRIBUTE_WIDTH_RATIO                                      3              //宽比
#define ATTRIBUTE_HEIGHT_RATIO                                     4              //高比
#define ATTRIBUTE_R                                                5              //R
#define ATTRIBUTE_G                                                6              //G
#define ATTRIBUTE_B                                                7              //B
#define ATTRIBUTE_ALPHA                                            8              //不透明度
#define ATTRIBUTE_FACE_DIRECTION                                   9              //朝向
#define ATTRIBUTE_SPEED                                            10             //速度
#define ATTRIBUTE_SPEED_DIRECTION                                  11            //速度方向
#define ATTRIBUTE_ACSPEED                                          12            //加速度
#define ATTRIBUTE_ACSPEED_DIRECTION                                13           //加速度方向
#define ATTRIBUTE_HORZ_RATIO                                       14            //横比
#define ATTRIBUTE_VERT_RATIO                                       15            //纵比
#define ATTRIBUTE_FOG                                              16            //雾化效果
#define ATTRIBUTE_DELETE                                           17           //消除效果
#define ATTRIBUTE_HIGHLIGHT                                        18            //高光效果
#define ATTRIBUTE_SHADE                                            19           //拖影效果
#define ATTRIBUTE_DELETE_OUT_OF_SCREEN                             20            //出屏即消
#define ATTRIBUTE_DETERMINATION                                    21            //无敌状态

#define CHANGETYPE_CHANGETO      1
#define CHANGETYPE_INCREASE      2
#define CHANGETYPE_DECREASE      3

#define CHANGEMANNER_LINEAR     1                 //正比
#define CHANGEMANNER_FIXED        2                 //固定
#define CHANGEMANNER_SIN           3                 //正弦

class THEvent{
public:
	UINT nOccurFrame;
	UINT nEventType;
public:
	THEvent(){}
	virtual ~THEvent(){}
	virtual void onEvent() = 0;
	bool operator >(THEvent* e){ return this->nOccurFrame > e->nOccurFrame; }
};

class EventCreation :public THEvent{
public:
	RenderObject *m_obj;
public:
	EventCreation() :m_obj(NULL){ nEventType = EVENT_CREATION; }
	EventCreation(RenderObject *obj) :m_obj(obj){ nEventType = EVENT_CREATION; }
	virtual ~EventCreation();
	virtual void onEvent();
};

class BulletEventCondition{
public:
	BYTE type;
	BYTE comparison;
	int dest;
};

class THBulletEvent{
public:
	int firstOccurFrame;
	BYTE attributeType;
	BYTE changeType;
	int value;
	BYTE changeManner;
	int changeTime;
	int repeatTime;               //重复发生次数
	int repeatFrameInterval;      //重复间隔  
public:
	THBulletEvent();
	bool IsOccuring(int frame);
};

#endif