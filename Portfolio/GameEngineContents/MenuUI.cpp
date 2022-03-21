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
}

void MenuUI::Update()
{
}

void MenuUI::Render()
{
	CreateRenderer("Lobby.bmp");
}