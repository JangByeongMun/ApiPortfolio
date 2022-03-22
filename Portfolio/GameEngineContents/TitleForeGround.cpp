#include "TitleForeGround.h"
#include <GameEngineBase/GameEngineWindow.h>

TitleForeGround::TitleForeGround() 
{
}

TitleForeGround::~TitleForeGround() 
{
}

void TitleForeGround::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("TitleOverlay.bmp", RenderPivot::CENTER, {0, 0});
	CreateRenderer("Titleshadow.bmp", RenderPivot::CENTER, { -260, 135 });
}

