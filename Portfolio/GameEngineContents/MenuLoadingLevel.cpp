#include "MenuLoadingLevel.h"
#include "RandomMenuLoading.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>

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
		GameEngine::GetInst().ChangeLevel("Play");
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
