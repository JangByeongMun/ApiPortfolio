#include "IntroPage.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

IntroPage::IntroPage()
	:ActorTime_(0.0f)
{
}

IntroPage::~IntroPage() 
{
}

void IntroPage::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CreateRenderer("IntroPage.bmp");
	CreateRenderer("IntroGameBy.bmp", RenderPivot::CENTER, {-250, -210});
	CreateRenderer("IntroName.bmp", RenderPivot::CENTER, { 0, -70 });

	GameEngineRenderer* IntroAnim = CreateRenderer(RenderPivot::CENTER, {0, 100});
	IntroAnim->CreateAnimation("IntroIcon.bmp", "IntroIcon", 0, 1, 0.25f, true);
	IntroAnim->ChangeAnimation("IntroIcon");
}

void IntroPage::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();
}
