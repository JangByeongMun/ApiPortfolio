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
	CreateRenderer("emptyscreen.bmp", 0)->SetPivot({2500, 1500});
	CreateRenderer("Menu.bmp");

	GameEngineRenderer* IntroRenderer = CreateRenderer(RenderPivot::CENTER, { -20, 100 });
	IntroRenderer->CreateAnimation("MenuIcon.bmp", "MenuIcon", 0, 1, 0.2f, true);
	IntroRenderer->ChangeAnimation("MenuIcon");

	CreateRenderer("MenuName.bmp", RenderPivot::CENTER, { 0, -200 });
}

void MenuStart::Update()
{

}