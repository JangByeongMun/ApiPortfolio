#include "OptionsMenu.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsGlobal.h"
#include "MenuLevel.h"

OptionsMenu::OptionsMenu() 
{
}

OptionsMenu::~OptionsMenu() 
{
}

void OptionsMenu::AddIndex(int _Index)
{
	CurrentIndex_ += _Index;
	if (CurrentIndex_ > 2)
	{
		CurrentIndex_ = 0;
	}
	if (CurrentIndex_ < 0)
	{
		CurrentIndex_ = 2;
	}

	Arrow_->SetPivot(ArrowPos_[CurrentIndex_]);
}

void OptionsMenu::AddValue(int _Value)
{
	switch (CurrentIndex_)
	{
	case 0:
		Option_SFX += _Value;
		if (Option_SFX > 10)
		{
			Option_SFX = 10;
		}
		if (Option_SFX < 0)
		{
			Option_SFX = 0;
		}
		break;
	case 1:
		Option_MUSIC += _Value;
		if (Option_MUSIC > 10)
		{
			Option_MUSIC = 10;
		}
		if (Option_MUSIC < 0)
		{
			Option_MUSIC = 0;
		}
		break;
	case 2:
		Option_MAPOPACITY += _Value;
		if (Option_MAPOPACITY > 10)
		{
			Option_MAPOPACITY = 10;
		}
		if (Option_MAPOPACITY < 0)
		{
			Option_MAPOPACITY = 0;
		}
		break;
	default:
		break;
	}
	
	MenuLevel* TmpLevel = dynamic_cast<MenuLevel*>(GetLevel());

	switch (CurrentIndex_)
	{
	case 0: 
		VolumeSfx_->SetIndex(10 - Option_SFX);
		GameEngineSound::SoundPlayOneShotWithVolume("plop.wav", 0, 1.0f * Option_SFX);
		break;
	case 1:
		VolumeMusic_->SetIndex(10 - Option_MUSIC);
		if (TmpLevel != nullptr)
		{
			TmpLevel->ChangeBGMVolume();
		}
		break;
	case 2:
		VolumeMapOpacity_->SetIndex(10 - Option_MAPOPACITY);
		break;
	default:
		break;
	}
}

void OptionsMenu::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4(1400, 3000));

	CreateRenderer("optionsmenu.bmp", RenderPivot::CENTER, { 0, 0 });
	
	CreateRenderer("optionsmenu_Name1.bmp", RenderPivot::CENTER, { -90, -140 });
	CreateRenderer("optionsmenu_Name2.bmp", RenderPivot::CENTER, { -90, -70 });
	CreateRenderer("optionsmenu_Name3.bmp", RenderPivot::CENTER, { -70, 0 });

	VolumeSfx_ = CreateRenderer("optionsmenu_VolumeRight.bmp", RenderPivot::CENTER, { 150, -140 });
	VolumeMusic_ = CreateRenderer("optionsmenu_VolumeLeft.bmp", RenderPivot::CENTER, { 150, -70 });
	VolumeMapOpacity_ = CreateRenderer("optionsmenu_VolumeRight.bmp", RenderPivot::CENTER, { 150, 0 });
	VolumeSfx_->SetIndex(10 - Option_SFX);
	VolumeMusic_->SetIndex(10 - Option_MUSIC);
	VolumeMapOpacity_->SetIndex(10 - Option_MAPOPACITY);
	
	Arrow_ = CreateRenderer("GameMenu_Arrow.bmp", RenderPivot::CENTER, { -170, -140 });
	ArrowPos_.push_back({ -170, -140 });
	ArrowPos_.push_back({ -170, -60 });
	ArrowPos_.push_back({ -215, 10 });
}