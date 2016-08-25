#ifndef GLOBAL_H
#define GLOBAL_H

class Global
{
public:
	enum StageEnum
	{
		STAGE_01,
		STAGE_02,
		STAGE_03,
		STAGE_04,
		STAGE_05,
		STAGE_06,
		STAGE_EX
	};

public:
	static StageEnum stageEnum;
};

#endif