#include "EndingLevel.h"
#include "EndingBackGround.h"
#include "EndingManager.h"
#include "TitleForeGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

EndingLevel::EndingLevel()
	: AllActors_({})
	, AllTimer_()
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
	CreateActor<TitleForeGround>(2);
	if (false == GameEngineInput::GetInst()->IsKey("EndingESC"))
	{
		GameEngineInput::GetInst()->CreateKey("EndingESC", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("EndingSpace", VK_SPACE);
	}
}

void EndingLevel::Update()
{
	if (
		true == GameEngineInput::GetInst()->IsDown("EndingESC") ||
		true == GameEngineInput::GetInst()->IsDown("EndingSpace")
		)
	{
		EndingPtr_->Stop();
		GameEngine::GetInst().ChangeLevel("Menu");
	}
}

void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	for (int i = 0; i < AllActors_.size(); i++)
	{
		AllActors_[i]->Off();
	}

	EndingPtr_->Play();
}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	EndingPtr_->Stop();
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