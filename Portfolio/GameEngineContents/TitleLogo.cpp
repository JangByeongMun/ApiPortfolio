#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

TitleLogo::TitleLogo()
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
}

void TitleLogo::Update()
{
}

void TitleLogo::Render()
{
	//DebugRectRender();
	CreateRenderer("MakeBy.bmp", RenderPivot::CENTER, { -180, -220 });
	CreateRenderer("TitleLogoText.bmp", RenderPivot::CENTER, { 0, -70 });
	CreateRenderer("TitleLogo.bmp", RenderPivot::CENTER, { 0, 100 });
}
