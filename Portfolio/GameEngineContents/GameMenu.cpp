#include "GameMenu.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "MenuLevel.h"

GameMenu::GameMenu() 
{
}

GameMenu::~GameMenu() 
{
}

void GameMenu::SelectMenu()
{
	MenuLevel* Level = static_cast<MenuLevel*>(GetLevel());
	Level->ChangeIndex(CurrentIndex_ + 3);
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

	ArrowPos_.push_back({-180, -140});
	ArrowPos_.push_back({-150, 100});
	ArrowPos_.push_back({-140, 180});
	ArrowRenderer_ = CreateRenderer("GameMenu_Arrow.bmp", RenderPivot::CENTER, ArrowPos_[0]);
}
