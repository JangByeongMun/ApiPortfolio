#include "Intro14.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro14::Intro14() 
	: MomRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro14::~Intro14() 
{
}

void Intro14::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	MomRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	MomRenderer_->CreateAnimation("Intro14_1.bmp", "Intro14_1_1", 0, 1, 0.1f, true);
	MomRenderer_->CreateAnimation("Intro14_1.bmp", "Intro14_1_2", 2, 3, 0.1f, true);
	MomRenderer_->CreateAnimation("Intro14_1.bmp", "Intro14_1_3", 4, 5, 0.1f, true);
	MomRenderer_->ChangeAnimation("Intro14_1_1");
}

void Intro14::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		MomRenderer_->ChangeAnimation("Intro14_1_2");
	}
	
	if (ActorTime_ >= 3 && false == Check2)
	{
		Check2 = true;
		MomRenderer_->ChangeAnimation("Intro14_1_3");
	}
}

