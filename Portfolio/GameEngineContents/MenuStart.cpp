#include "MenuStart.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>

MenuStart::MenuStart() 
{
}

MenuStart::~MenuStart() 
{
}

void MenuStart::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CreateRenderer("emptyscreen.bmp");
	CreateRenderer("Menu.bmp");

	GameEngineRenderer* IntroRenderer = CreateRenderer(RenderPivot::CENTER, { 0, 100 });
	IntroRenderer->CreateAnimation("MenuIcon.bmp", "MenuIcon", 0, 1, 0.3f, true);
	IntroRenderer->ChangeAnimation("MenuIcon");

	CreateRenderer("MenuName.bmp", RenderPivot::CENTER, { 0, -200 });
}

void MenuStart::Update()
{

}