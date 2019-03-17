#ifndef RANK_SELECT_MENU_ITEM_H
#define RANK_SELECT_MENU_ITEM_H

#include <THEngine.h>

using namespace THEngine;

class RankSelectMenuItem : public MenuItem
{
public:
	static Ptr<Texture> texRank;

	enum Type
	{
		EASY,
		NORMAL,
		HARD,
		LUNATIC
	};

private:
	Type type;

public:
	RankSelectMenuItem();
	virtual ~RankSelectMenuItem() = default;

	virtual void OnStart() override;

	void SetType(Type type);

	void Enter();

	void Exit();
};

#endif