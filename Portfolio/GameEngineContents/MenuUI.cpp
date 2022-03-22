#include "MenuUI.h"
#include <GameEngineBase/GameEngineWindow.h>

MenuUI::MenuUI() 
{
}

MenuUI::~MenuUI() 
{
}

void MenuUI::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CreateRenderer("Menu.bmp");
	CreateRenderer("MenuIcon1.bmp", RenderPivot::CENTER, {0, 100});
	CreateRenderer("MenuIcon2.bmp", RenderPivot::CENTER, { 0, 100 });
	CreateRenderer("MenuName.bmp", RenderPivot::CENTER, { 0, -200 });

}