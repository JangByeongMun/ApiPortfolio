#include "MenuUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

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

	GameEngineRenderer* IntroAnim = CreateRenderer(RenderPivot::CENTER, { 0, 100 });
	IntroAnim->CreateAnimation("MenuIcon.bmp", "MenuIcon", 0, 1, 0.3f, true);
	IntroAnim->ChangeAnimation("MenuIcon");
	
	CreateRenderer("MenuName.bmp", RenderPivot::CENTER, { 0, -200 });

}