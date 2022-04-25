#include <GameEngine/GameEngine.h>
#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "IntroPage.h"
#include "TitleForeGround.h"
#include "IntroManager.h"
#include <GameEngineBase/GameEngineInput.h>

TitleLevel::TitleLevel() 
	: IntroPtr_()
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0);
	CreateActor<IntroPage>(1);
	IntroPtr_ = CreateActor<IntroManager>(1);

	CreateActor<TitleForeGround>(1);


	if (false == GameEngineInput::GetInst()->IsKey("TitleESC"))
	{
		GameEngineInput::GetInst()->CreateKey("TitleESC", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("TitleSpace", VK_SPACE);
	}
}

void TitleLevel::Update()
{
	if (
		true == GameEngineInput::GetInst()->IsDown("TitleESC") ||
		true == GameEngineInput::GetInst()->IsDown("TitleSpace")
		)
	{
		IntroPtr_->Stop();
		GameEngine::GetInst().ChangeLevel("Menu");
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	IntroPtr_->Play();
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	IntroPtr_->Stop();
}