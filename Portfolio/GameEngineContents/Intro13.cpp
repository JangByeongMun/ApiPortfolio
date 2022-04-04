#include "Intro13.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro13::Intro13() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro13::~Intro13() 
{
}

void Intro13::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("Intro13_1.bmp", "Intro13_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro13_1");
}

void Intro13::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	//if (ActorTime_ >= 2 && false == Check1)
	//{
	//	Check1 = true;
	//}
	//
	//if (ActorTime_ >= 3 && false == Check2)
	//{
	//	Check2 = true;
	//}
}

