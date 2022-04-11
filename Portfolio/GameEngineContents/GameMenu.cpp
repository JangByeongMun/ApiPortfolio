#include "GameMenu.h"
#include <GameEngineBase/GameEngineWindow.h>

GameMenu::GameMenu() 
{
}

GameMenu::~GameMenu() 
{
}

void GameMenu::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4(0, 2000));

	CreateRenderer("GameMenu.bmp", RenderPivot::CENTER, { 0, 0 });
	CreateRenderer("GameMenu2.bmp", RenderPivot::CENTER, { -640, 0 });

	CreateRenderer("GameMenu_Menu1.bmp", RenderPivot::CENTER, { -20, -160 });
	CreateRenderer("GameMenu_Menu2.bmp", RenderPivot::CENTER, { -10, -80 });
	CreateRenderer("GameMenu_Menu3.bmp", RenderPivot::CENTER, { 0, 0 });
	CreateRenderer("GameMenu_Menu4.bmp", RenderPivot::CENTER, { 10, 80 });
	CreateRenderer("GameMenu_Menu5.bmp", RenderPivot::CENTER, { 20, 160 });
	CreateRenderer("GameMenu_Arrow.bmp", RenderPivot::CENTER, { -160, 0 });
}

void GameMenu::Update()
{
}

