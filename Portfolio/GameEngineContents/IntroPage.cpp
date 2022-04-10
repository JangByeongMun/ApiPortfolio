#include "IntroPage.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

void MakeRenderer()
{
}

IntroPage::IntroPage()
	: ActorTime_(0.0f)
	, PageRenderer_()
	, Check1()
	, Check2()
{
}

IntroPage::~IntroPage() 
{
}

void IntroPage::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	PageRenderer_ = CreateRenderer("IntroPage.bmp");
}

void IntroPage::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 1 && false == Check1)
	{
		Check1 = true;
		CreateRenderer("IntroGameBy.bmp", RenderPivot::CENTER, { -250, -210 })->Death(2.0f + 2.0f);
		CreateRenderer("IntroName.bmp", RenderPivot::CENTER, { 0, -70 })->Death(2.0f + 2.0f);

		GameEngineRenderer* IntroAnim = CreateRenderer(RenderPivot::CENTER, { 0, 100 });
		IntroAnim->CreateAnimation("IntroIcon.bmp", "IntroIcon", 0, 1, 0.2f, true);
		IntroAnim->ChangeAnimation("IntroIcon");
		IntroAnim->Death(2.0f);
	}

	if (ActorTime_ >= 3.0f && false == Check2)
	{
		Check2 = true;

		GameEngineRenderer* IntroAnim = CreateRenderer(RenderPivot::CENTER, { 0, 100 });
		IntroAnim->CreateAnimation("epilogue15_3.bmp", "epilogue15_3", 0, 1, 0.2f, true);
		IntroAnim->ChangeAnimation("epilogue15_3");
		IntroAnim->Death(2.0f);
	}

	if (ActorTime_ >= 5.5f)
	{
		PageRenderer_->SetPivot(float4::Lerp({ 0, 0 }, { -2000, 0 }, ActorTime_ - 5.5f) * 4);
	}
}