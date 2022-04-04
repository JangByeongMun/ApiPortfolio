#include "Intro11.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro11::Intro11() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro11::~Intro11() 
{
}

void Intro11::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("Intro11_1.bmp", "Intro11_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro11_1");
}

void Intro11::Update()
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

