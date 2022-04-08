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
#include "EndingManager.h"
#include "EndingManager2.h"

EndingLevel::EndingLevel()
	: AllActors_({})
	, AllTimer_()
	, LevelTime_(0.0f)
	, PrevTime_(0.0f)
	, CurrentIndex_(0)
	, BgmPlayer_()
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

	BgmPlayer_ = GameEngineSound::SoundPlayControl("Ending.ogg");
	BgmPlayer_.SetVolume(0.1f);
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