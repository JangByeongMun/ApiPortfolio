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
#include "Credit11.h"
#include "Credit12.h"
#include "Credit13.h"
#include "Credit14.h"
#include "Credit15.h"

EndingLevel::EndingLevel()
	: AllActors_({})
	, AllTimer_()
	, LevelTime_(0.0f)
	, CurrentIndex_(0)
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Loading()
{
	CreateActor<EndingBackGround>(0);
}

void EndingLevel::Update()
{
	LevelTime_ += GameEngineTime::GetDeltaTime();
	
	for (int i = 0; i < AllActors_.size(); i++)
	{
		if (i * 2.0f <= LevelTime_ && LevelTime_ < (i + 1) * 2.0f)
		{
			ChangeEndingCredit(i);
		}
	}

	if (false == AllActors_[CurrentIndex_]->IsUpdate())
	{
		for (int i = 0; i < AllActors_.size(); i++)
		{
			if (i == CurrentIndex_)
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
	AllActors_.push_back(CreateActor<Credit11>(1));
	AllActors_.push_back(CreateActor<Credit12>(1));
	AllActors_.push_back(CreateActor<Credit13>(1));
	AllActors_.push_back(CreateActor<Credit14>(1));
	AllActors_.push_back(CreateActor<Credit15>(1));

	for (int i = 0; i < AllActors_.size(); i++)
	{
		AllActors_[i]->Off();
	}
}

void EndingLevel::LevelChangeEnd()
{
	
}