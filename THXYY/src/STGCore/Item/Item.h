#ifndef ITEM_H
#define ITEM_H

#include <THEngine.h>

using namespace THEngine;

class Item : public Sprite
{
protected:
	float hitRange;
	bool goToPlayer = false;

	int frame = 0;

	bool gotFromHigh = false;

public:
	Item();
	virtual ~Item();

	virtual void Update() override;

	virtual void OnGot();

	void GoToPlayer();

	inline void SetPosition(float x, float y)
	{
		Sprite::SetPosition(Vector3f(x, y, 50.0f));
	}

	friend class STGEngine;
};

#endif