#include "IntroPage.h"
#include <GameEngineBase/GameEngineWindow.h>

IntroPage::IntroPage() 
{
}

IntroPage::~IntroPage() 
{
}

void IntroPage::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CreateRenderer("IntroPage.bmp");
	CreateRenderer("IntroGameBy.bmp", RenderPivot::CENTER, {-250, -210});
	CreateRenderer("IntroName.bmp", RenderPivot::CENTER, { 0, -70 });
	CreateRenderer("IntroIcon1.bmp", RenderPivot::CENTER, { 0, 100 });
	CreateRenderer("IntroIcon2.bmp", RenderPivot::CENTER, { 0, 100 });
}

void IntroPage::Update()
{

}