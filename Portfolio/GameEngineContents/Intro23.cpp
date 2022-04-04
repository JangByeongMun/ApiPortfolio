#include "Intro23.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro23::Intro23() 
	: DoorRenderer_(nullptr)
	, IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro23::~Intro23() 
{
}

void Intro23::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	DoorRenderer_ = CreateRenderer("Intro23_1.bmp", RenderPivot::CENTER, { -20, -100 });

	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { 40, 190 });
	IsaacRenderer_->CreateAnimation("Intro23_3.bmp", "Intro23_3", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro23_4.bmp", "Intro23_4", 0, 1, 0.1f, true);
	IsaacRenderer_->ChangeAnimation("Intro23_3");
}

void Intro23::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		DoorRenderer_->SetImage("Intro23_2.bmp");
		DoorRenderer_->SetPivot({20, -110});
		IsaacRenderer_->ChangeAnimation("Intro23_4");
		IsaacRenderer_->SetPivot({-35, 40});
	}
	
	if (ActorTime_ >= 3 && false == Check2)
	{
		Check2 = true;
	}
}

