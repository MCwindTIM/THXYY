#ifndef THFOG_H
#define THFOG_H

#define ENEMY_FOG_RED1                         1
#define ENEMY_FOG_GREEN1                     2
#define ENEMY_FOG_BLUE1                        3
#define ENEMY_FOG_YELLOW1                   4
#define ENEMY_FOG_RED2                         5
#define ENEMY_FOG_GREEN2                    6
#define ENEMY_FOG_BLUE2                        7
#define ENEMY_FOG_YELLOW2                   8

#define BULLET_FOG_WHITE1                      1
#define BULLET_FOG_RED                            2
#define BULLET_FOG_PURPLE                      3
#define BULLET_FOG_BLUE                          4
#define BULLET_FOG_TEAL                           5
#define BULLET_FOG_GREEN                       6
#define BULLET_FOG_YELLOW                     7
#define BULLET_FOG_WHITE2                      8

#include "../RenderObject.h"

class THFog :public RenderObject
{
protected:
	BYTE type;
	int frame;
	int r, g, b;
public:
	virtual void Update(){
		frame++;
	}
};

class THEnemyFog :public THFog
{
public:
	THEnemyFog(BYTE type);
	virtual void Init();
	virtual void Draw();
};

class THBulletFog :public THFog{
public:
	THBulletFog(BYTE type);
	virtual void Init();
	virtual void Draw();
};

#endif