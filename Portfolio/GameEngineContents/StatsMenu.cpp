#include "StatsMenu.h"
#include <GameEngineBase/GameEngineWindow.h>

StatsMenu::StatsMenu() 
{
}

StatsMenu::~StatsMenu() 
{
}

void StatsMenu::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4(1400, 1000));
	CreateRenderer("sketches1.bmp", RenderPivot::CENTER, { -70, 250 });
	CreateRenderer("sketches2.bmp", RenderPivot::CENTER, { 140, -230 });

	CreateRenderer("statsmenu1.bmp", RenderPivot::CENTER, { -270, 0 });
	CreateRenderer("statsmenu2.bmp", RenderPivot::CENTER, { 270, 0 });

	CreateRenderer("statsmenu_Right1.bmp", RenderPivot::CENTER, { 280, -130 });
	CreateRenderer("statsmenu_Right2.bmp", RenderPivot::CENTER, { 280, -50 });
	CreateRenderer("statsmenu_Right3.bmp", RenderPivot::CENTER, { 280, 50 });

	CreateRenderer("GameMenu_Arrow.bmp", RenderPivot::CENTER, { 130, -120 });
}

