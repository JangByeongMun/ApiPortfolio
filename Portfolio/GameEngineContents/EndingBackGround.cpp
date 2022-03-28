#include "EndingBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

EndingBackGround::EndingBackGround() 
{
}

EndingBackGround::~EndingBackGround() 
{
}

void EndingBackGround::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CreateRenderer("EndingBG.bmp");
	CreateRenderer("epilogueTest.bmp", RenderPivot::CENTER, {-60, -50});
}
