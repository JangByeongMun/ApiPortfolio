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
	AllOptionValues[CurrentIndex_] += _Value;
	if (AllOptionValues[CurrentIndex_] > 10)
	{
		AllOptionValues[CurrentIndex_] = 10;
	}
	if (AllOptionValues[CurrentIndex_] < 0)
	{
		AllOptionValues[CurrentIndex_] = 0;
	}

	MenuLevel* TmpLevel = dynamic_cast<MenuLevel*>(GetLevel());

	switch (CurrentIndex_)
	{
	case 0: 
		VolumeSfx_->SetIndex(10 - AllOptionValues[CurrentIndex_]);
		Option_SFX = AllOptionValues[CurrentIndex_];
		GameEngineSound::SoundPlayOneShotWithVolume("plop.wav", 0, 0.01f * Option_SFX);
		break;
	case 1:
		VolumeMusic_->SetIndex(10 - AllOptionValues[CurrentIndex_]);
		Option_MUSIC = AllOptionValues[CurrentIndex_];
		if (TmpLevel != nullptr)
		{
			TmpLevel->ChangeBGMVolume();
		}
		break;
	case 2:
		VolumeMapOpacity_->SetIndex(10 - AllOptionValues[CurrentIndex_]);
		Option_MAPOPACITY = AllOptionValues[CurrentIndex_];
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
	VolumeSfx_->SetIndex(10 - AllOptionValues[0]);
	VolumeMusic_->SetIndex(10 - AllOptionValues[1]);
	VolumeMapOpacity_->SetIndex(10 - AllOptionValues[2]);
	
	Arrow_ = CreateRenderer("GameMenu_Arrow.bmp", RenderPivot::CENTER, { -170, -140 });
	ArrowPos_.push_back({ -170, -140 });
	ArrowPos_.push_back({ -170, -60 });
	ArrowPos_.push_back({ -215, 10 });
}