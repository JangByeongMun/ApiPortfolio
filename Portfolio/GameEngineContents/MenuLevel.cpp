#include "MenuLevel.h"
#include "MenuStart.h"
#include "MenuFileSelect.h"
#include "GameMenu.h"
#include "CharacterMenu.h"
#include "StatsMenu.h"
#include "OptionsMenu.h"

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>

MenuLevel::MenuLevel()
	: CurrentLevelTime_(0)
	, AllScreenPos_()
	, CurrentPos_()
	, ChangeStartTime_(0)
	, IsChanging_(false)
	, ChangeIndex_(0)
	, CurrentIndex_(0)
{
}

MenuLevel::~MenuLevel() 
{
}

void MenuLevel::Loading()
{
	Index0_ = CreateActor<MenuStart>(0);
	Index1_ = CreateActor<MenuFileSelect>(0);
	Index2_ = CreateActor<GameMenu>(0);
	Index3_ = CreateActor<CharacterMenu>(0);
	Index4_ = CreateActor<StatsMenu>(0);
	Index5_ = CreateActor<OptionsMenu>(0);

	if (false == GameEngineInput::GetInst()->IsKey("MenuOK"))
	{
		GameEngineInput::GetInst()->CreateKey("MenuOK", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("MenuESC", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("MenuLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MenuRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MenuUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MenuDown", VK_DOWN);
	}

	AllScreenPos_.push_back({0, 0});
	AllScreenPos_.push_back({0, 675});
	AllScreenPos_.push_back({0, 2000});
	AllScreenPos_.push_back({1400, 2000});
	AllScreenPos_.push_back({1400, 1000});
	AllScreenPos_.push_back({1400, 3000});
	AllScreenPos_.push_back({0, 3000});
	CurrentIndex_ = 0;
}

void MenuLevel::Update()
{
	CurrentLevelTime_ += GameEngineTime::GetDeltaTime();

	if (true == GameEngineInput::GetInst()->IsDown("MenuOK"))
	{
		switch (CurrentIndex_)
		{
		case 0:
			ChangeIndex(1);
			break;
		case 1:
			ChangeIndex(2);
			break;
		case 2:
			Index2_->SelectMenu();
			break;
		case 3:
			Index3_->SelectIndex();
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("MenuESC"))
	{
		switch (CurrentIndex_)
		{
		case 0:
			GameEngineWindow::GetInst().Off();
			break;
		case 1:
			ChangeIndex(0);
			break;
		case 2:
			ChangeIndex(1);
			break;
		case 3:
			ChangeIndex(2);
			break;
		case 4:
			ChangeIndex(2);
			break;
		case 5:
			ChangeIndex(2);
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("MenuLeft"))
	{
		switch (CurrentIndex_)
		{
		case 0:
			break;
		case 1:
			Index1_->ChangeFile(Index1_->GetCurrentIndex() - 1);
			break;
		case 2:
			break;
		case 3:
			Index3_->AddIndex(-1);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("MenuRight"))
	{
		switch (CurrentIndex_)
		{
		case 0:
			break;
		case 1:
			Index1_->ChangeFile(Index1_->GetCurrentIndex() + 1);
			break;
		case 2:
			break;
		case 3:
			Index3_->AddIndex(1);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("MenuUp"))
	{
		switch (CurrentIndex_)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			Index2_->AddMenuIndex(-1);
			break;
		case 3:
			Index3_->AddDifficult(-1);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("MenuDown"))
	{
		switch (CurrentIndex_)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			Index2_->AddMenuIndex(1);
			break;
		case 3:
			Index3_->AddDifficult(1);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}

	if (true == IsChanging_)
	{
		SetCameraPos(float4::Lerp(CurrentPos_, AllScreenPos_[ChangeIndex_], (CurrentLevelTime_ - ChangeStartTime_) * 3));
		if ((CurrentLevelTime_ - ChangeStartTime_) >= 1)
		{
			IsChanging_ = false;
		}
	}
}

void MenuLevel::LevelChangeStart()
{
}

void MenuLevel::LevelChangeEnd()
{
}

void MenuLevel::ChangeIndex(int _Index)
{
	IsChanging_ = true;
	ChangeStartTime_ = CurrentLevelTime_;
	ChangeIndex_ = _Index;
	CurrentIndex_ = ChangeIndex_;
	CurrentPos_ = GetCameraPos();
}
