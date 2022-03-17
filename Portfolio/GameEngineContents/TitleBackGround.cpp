#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

TitleBackGround::TitleBackGround() 
{
}

TitleBackGround::~TitleBackGround() 
{
}

void TitleBackGround::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	SetScale(GameEngineWindow::GetInst().GetScale());
}

void TitleBackGround::Update()
{
}

void TitleBackGround::Render()
{
	DebugRectRender();
}
