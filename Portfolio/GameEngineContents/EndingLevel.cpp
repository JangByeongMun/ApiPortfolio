#include "EndingLevel.h"
#include "EndingBackGround.h"
#include "EndingManager.h"

EndingLevel::EndingLevel()
	: AllActors_({})
	, AllTimer_()
	, LevelTime_(0.0f)
	, PrevTime_(0.0f)
	, CurrentIndex_(0)
	, EndingPtr_()
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Loading()
{
	CreateActor<EndingBackGround>(0);
	EndingPtr_ = CreateActor<EndingManager>(1);
}

void EndingLevel::Update()
{
	LevelTime_ += GameEngineTime::GetDeltaTime();
}

void EndingLevel::LevelChangeStart()
{
	LevelTime_ = 0.0f;

	for (int i = 0; i < AllActors_.size(); i++)
	{
		AllActors_[i]->Off();
	}

	EndingPtr_->Play();
}

void EndingLevel::LevelChangeEnd()
{
	
}

float EndingLevel::CurrentTimer(int _Index)
{
	if (_Index >= AllTimer_.size())
	{
		return -1;
	}

	float ReturnF = 0.0f;
	for (int i = 0; i <= _Index; i++)
	{
		ReturnF += AllTimer_[i];
	}

	return ReturnF;
}