#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "TitleLogo.h"

TitleLogo::TitleLogo()
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	SetScale({ 500, 500 });
}

void TitleLogo::Update()
{
}

void TitleLogo::Render()
{
	DebugRectRender();
}
