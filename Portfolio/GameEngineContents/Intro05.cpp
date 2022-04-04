#include "Intro05.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro05::Intro05() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro05::~Intro05() 
{
}

void Intro05::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("intro05_1.bmp", RenderPivot::CENTER, { 0, 0 });
	CreateRenderer("intro05_4.bmp", RenderPivot::CENTER, { 160, 280 });

	MomRenderer = CreateRenderer(RenderPivot::CENTER, { -20, 0 });
	MomRenderer->CreateAnimation("Intro05_2.bmp", "Intro05_2", 0, 1, 0.1f, true);
	MomRenderer->CreateAnimation("Intro05_5.bmp", "Intro05_5", 0, 1, 0.1f, true);
	MomRenderer->ChangeAnimation("Intro05_2");

	IsaacRenderer = CreateRenderer(RenderPivot::CENTER, { 190, 170 });
	IsaacRenderer->CreateAnimation("Intro05_3.bmp", "Intro05_3", 0, 1, 0.1f, true);
	IsaacRenderer->CreateAnimation("Intro05_6.bmp", "Intro05_6", 0, 0, 0.1f, true);
	IsaacRenderer->ChangeAnimation("Intro05_3");
}

void Intro05::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		MomRenderer->ChangeAnimation("Intro05_5");
	}
	
	if (ActorTime_ >= 4 && false == Check2)
	{
		Check2 = true;
		IsaacRenderer->ChangeAnimation("Intro05_6");
	}
}

