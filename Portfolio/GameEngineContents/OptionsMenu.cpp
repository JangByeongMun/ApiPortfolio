#include "OptionsMenu.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

OptionsMenu::OptionsMenu() 
{
}

OptionsMenu::~OptionsMenu() 
{
}

void OptionsMenu::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4(1400, 3000));

	CreateRenderer("optionsmenu.bmp", RenderPivot::CENTER, { 0, 0 });
	
	CreateRenderer("optionsmenu_Name1.bmp", RenderPivot::CENTER, { -120, -140 });
	CreateRenderer("optionsmenu_Name2.bmp", RenderPivot::CENTER, { -120, -70 });
	CreateRenderer("optionsmenu_Name3.bmp", RenderPivot::CENTER, { -100, 0 });
	CreateRenderer("optionsmenu_Name4.bmp", RenderPivot::CENTER, { -100, 70 });

	CreateRenderer("optionsmenu_VolumeRight.bmp", RenderPivot::CENTER, { 120, -140 })->SetIndex(0);
	CreateRenderer("optionsmenu_VolumeLeft.bmp", RenderPivot::CENTER, { 120, -70 })->SetIndex(0);
	CreateRenderer("optionsmenu_VolumeRight.bmp", RenderPivot::CENTER, { 120, 0 })->SetIndex(0);

}

