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

	CreateRenderer("LoadingBackground.bmp");
	CreateRenderer("LoadingLight.bmp");
}
