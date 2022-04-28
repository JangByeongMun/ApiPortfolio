#include "MenuLoadingLevel.h"
#include "RandomMenuLoading.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include "BindingOfIsaac.h"
#include "ContentsGlobal.h"
#include "Player.h"

MenuLoadingLevel::MenuLoadingLevel() 
	: Loading_(nullptr)
	, LoadingTimer_(0)
{
}

MenuLoadingLevel::~MenuLoadingLevel() 
{
}

void MenuLoadingLevel::Loading()
{
	Loading_ = CreateActor<RandomMenuLoading>(0);
}

void MenuLoadingLevel::Update()
{
	LoadingTimer_ -= GameEngineTime::GetDeltaTime();

	if (LoadingTimer_ <= 0)
	{
		BindingOfIsaac* TmpEngine = dynamic_cast<BindingOfIsaac*>(&GameEngine::GetInst());
		if (nullptr != TmpEngine)
		{
			CurrentFloor = 1;
			Player::MainPlayer = nullptr;
			TmpEngine->ResetPlayLevel("Play");
			TmpEngine->ChangeLevel("Play");
		}
	}
}

void MenuLoadingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Loading_->RandomLoading();
	LoadingTimer_ = 4.0f;
}

void MenuLoadingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
