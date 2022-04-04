#include "Intro22.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro22::Intro22() 
	: DoorRenderer_(nullptr)
	, IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro22::~Intro22() 
{
}

void Intro22::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	DoorRenderer_ = CreateRenderer("intro22_1.bmp", RenderPivot::CENTER, { -20, 80 });

	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	IsaacRenderer_->CreateAnimation("Intro22_2.bmp", "Intro22_2", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro22_4.bmp", "Intro22_4", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
	IsaacRenderer_->ChangeAnimation("None");
}

void Intro22::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();
	
	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		DoorRenderer_->SetImage("intro22_3.bmp");
		DoorRenderer_->SetPivot({150, 120});

		IsaacRenderer_->ChangeAnimation("Intro22_2");
		IsaacRenderer_->SetPivot({-150, 50});
	}
	
	if (ActorTime_ >= 3 && false == Check2)
	{
		Check2 = true;
		IsaacRenderer_->ChangeAnimation("Intro22_4");
	}
}

