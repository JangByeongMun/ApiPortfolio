#include "Intro12.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro12::Intro12() 
	: DoorRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro12::~Intro12() 
{
}

void Intro12::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	DoorRenderer_ = CreateRenderer(RenderPivot::CENTER, { -30, -30 });
	DoorRenderer_->CreateAnimation("Intro12_1.bmp", "Intro12_1_1", 0, 0, 0.1f, true);
	DoorRenderer_->CreateAnimation("Intro12_1.bmp", "Intro12_1_2", 1, 1, 0.1f, true);
	DoorRenderer_->ChangeAnimation("Intro12_1_2");

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 160, 220 });
	renderer->CreateAnimation("Intro12_2.bmp", "Intro12_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro12_2");
}

void Intro12::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		DoorRenderer_->ChangeAnimation("Intro12_1_1");
	}

	//if (ActorTime_ >= 3 && false == Check2)
	//{
	//	Check2 = true;
	//}
}

