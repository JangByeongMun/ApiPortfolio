#include "Intro15.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro15::Intro15() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro15::~Intro15() 
{
}

void Intro15::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("Intro15_1.bmp", "Intro15_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro15_1");
}

void Intro15::Update()
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

