#include "Intro20.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro20::Intro20() 
	: DoorRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro20::~Intro20() 
{
}

void Intro20::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	DoorRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 });
	DoorRenderer_->CreateAnimation("Intro20_1.bmp", "Intro20_1_1", 0, 0, 0.1f, false);
	DoorRenderer_->CreateAnimation("Intro20_1.bmp", "Intro20_1_2", 1, 1, 0.1f, false);
	DoorRenderer_->ChangeAnimation("Intro20_1_1");
}

void Intro20::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		DoorRenderer_->ChangeAnimation("Intro20_1_2");
		CreateRenderer("Intro20_2.bmp", RenderPivot::CENTER, { -10, -180 });
	}
	
	//if (ActorTime_ >= 3 && false == Check2)
	//{
	//	Check2 = true;
	//}
}

