#ifndef FAIRY_H
#define FAIRY_H

#include "Enemy.h"

class Fairy : public Enemy
{
public:
	Fairy();
	virtual ~Fairy();

	virtual void Update() override;
};

///////////////////////////////////////////

class BlueFairy01 : public Fairy
{
public:
	BlueFairy01();
	virtual ~BlueFairy01();
};

///////////////////////////////////////////

class BlueFairy02 : public Fairy
{
public:
	BlueFairy02();
	virtual ~BlueFairy02();
};

///////////////////////////////////////////

class RedFairy01 : public Fairy
{
public:
	RedFairy01();
	virtual ~RedFairy01();
};

///////////////////////////////////////////

class RedFairy02 : public Fairy
{
public:
	RedFairy02();
	virtual ~RedFairy02();
};

///////////////////////////////////////////

class GreenFairy01 : public Fairy
{
public:
	GreenFairy01();
	virtual ~GreenFairy01();
};

///////////////////////////////////////////

class GreenFairy02 : public Fairy
{
public:
	GreenFairy02();
	virtual ~GreenFairy02();
};

///////////////////////////////////////////

class YellowFairy01 : public Fairy
{
public:
	YellowFairy01();
	virtual ~YellowFairy01();
};

///////////////////////////////////////////

class YellowFairy02 : public Fairy
{
public:
	YellowFairy02();
	virtual ~YellowFairy02();
};

#endif