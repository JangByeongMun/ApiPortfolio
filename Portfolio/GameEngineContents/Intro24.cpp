#include "Intro24.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro24::Intro24() 
	: DoorRenderer_(nullptr)
	, IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
	, Check3(false)
{
}

Intro24::~Intro24() 
{
}

void Intro24::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	DoorRenderer_ = CreateRenderer("Intro24_1.bmp", RenderPivot::CENTER, { 90, 120 });

	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { -150, 20 });
	IsaacRenderer_->CreateAnimation("Intro24_2.bmp", "Intro24_2", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro24_3.bmp", "Intro24_3", 0, 0, 0.1f, false);
	IsaacRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
	IsaacRenderer_->ChangeAnimation("Intro24_2");
}

void Intro24::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();
	
	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		IsaacRenderer_->ChangeAnimation("Intro24_3");
		IsaacRenderer_->SetPivot({ -50, -20 });
	}
	
	if (ActorTime_ >= 2.2f && false == Check2)
	{
		Check2 = true;
		IsaacRenderer_->ChangeAnimation("None");
		DoorRenderer_->SetImage("Intro24_4.bmp");
	}
	
	if (ActorTime_ >= 2.4f && false == Check3)
	{
		Check3 = true;
		DoorRenderer_->SetImage("Intro24_1.bmp");
	}
}

