#include "Intro10.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro10::Intro10() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro10::~Intro10() 
{
}

void Intro10::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("Intro10_1.bmp", "Intro10_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro10_1");
}

void Intro10::Update()
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

