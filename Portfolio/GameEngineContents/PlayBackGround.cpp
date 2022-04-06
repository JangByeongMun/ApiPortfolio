#include "PlayBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayBackGround::PlayBackGround() 
{
}

PlayBackGround::~PlayBackGround() 
{
}

void PlayBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRendererToScale("bgblack.bmp", GameEngineWindow::GetScale());
}

