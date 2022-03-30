#include "EndingLevel.h"
#include "EndingBackGround.h"
#include "Credit01.h"
#include "Credit02.h"
#include "Credit03.h"
#include "Credit04.h"
#include "Credit05.h"
#include "Credit06.h"
#include "Credit07.h"
#include "Credit08.h"
#include "Credit09.h"
#include "Credit10.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Loading()
{
	CreateActor<EndingBackGround>(0);
}

int test = 0;
void EndingLevel::Update()
{
	LevelTime_ += GameEngineTime::GetDeltaTime();

	if (0.0f <= LevelTime_ && LevelTime_ < 3.0f)
	{
		test = 0;
	}
	else if (3.0f <= LevelTime_ && LevelTime_ < 6.0f)
	{
		test = 1;
	}
	else if (6.0f <= LevelTime_ && LevelTime_ < 9.0f)
	{
		test = 2;
	}
	else if (9.0f <= LevelTime_ && LevelTime_ < 12.0f)
	{
		test = 3;
	}
	else if (12.0f <= LevelTime_ && LevelTime_ < 15.0f)
	{
		test = 4;
	}
	else if (15.0f <= LevelTime_ && LevelTime_ < 18.0f)
	{
		test = 5;
	}
	else if (18.0f <= LevelTime_ && LevelTime_ < 21.0f)
	{
		test = 6;
	}
	else if (21.0f <= LevelTime_ && LevelTime_ < 24.0f)
	{
		test = 7;
	}
	else if (24.0f <= LevelTime_ && LevelTime_ < 27.0f)
	{
		test = 8;
	}
	else if (27.0f <= LevelTime_ && LevelTime_ < 30.0f)
	{
		test = 9;
	}

	if (false == AllActors_[test]->IsUpdate())
	{
		for (int i = 0; i < AllActors_.size(); i++)
		{
			if (i == test)
			{
				AllActors_[i]->On();
			}
			else
			{
				AllActors_[i]->Off();
			}
		}
	}
}

void EndingLevel::LevelChangeStart()
{
	LevelTime_ = 0.0f;
	AllActors_.push_back(CreateActor<Credit01>(1));
	AllActors_.push_back(CreateActor<Credit02>(1));
	AllActors_.push_back(CreateActor<Credit03>(1));
	AllActors_.push_back(CreateActor<Credit04>(1));
	AllActors_.push_back(CreateActor<Credit05>(1));
	AllActors_.push_back(CreateActor<Credit06>(1));
	AllActors_.push_back(CreateActor<Credit07>(1));
	AllActors_.push_back(CreateActor<Credit08>(1));
	AllActors_.push_back(CreateActor<Credit09>(1));
	AllActors_.push_back(CreateActor<Credit10>(1));

	for (int i = 0; i < AllActors_.size(); i++)
	{
		AllActors_[i]->Off();
	}
}

void EndingLevel::LevelChangeEnd()
{
	
}