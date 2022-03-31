#include "MenuFileSelect.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

MenuFileSelect::MenuFileSelect() 
{
}

MenuFileSelect::~MenuFileSelect() 
{
}

void MenuFileSelect::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4(0, 720));
	CreateRenderer("MenuFileSelect1.bmp");
	CreateRenderer("MenuFileSelect2.bmp");
	CreateRenderer("MenuFileSelect3.bmp");
}