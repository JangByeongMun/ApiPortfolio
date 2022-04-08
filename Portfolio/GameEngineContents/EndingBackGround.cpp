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
}

void EndingBackGround::Update()
{

}