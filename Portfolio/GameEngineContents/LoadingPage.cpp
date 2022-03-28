#include "LoadingPage.h"
#include <GameEngineBase/GameEngineWindow.h>

LoadingPage::LoadingPage() 
{
}

LoadingPage::~LoadingPage() 
{
}

void LoadingPage::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("bgblack.bmp");
	CreateRenderer("LoadingLight.bmp");
}
