#include "Intro07.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro07::Intro07() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro07::~Intro07() 
{
}

void Intro07::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("intro05_1.bmp", RenderPivot::CENTER, { 0, 0 });
	CreateRenderer("intro05_4.bmp", RenderPivot::CENTER, { 160, 280 });

	CreateRenderer("intro07_1.bmp", RenderPivot::CENTER, { -20, 50 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 190, 170 });
	renderer->CreateAnimation("Intro07_2.bmp", "Intro07_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro07_2");
}

void Intro07::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	//if (ActorTime_ >= 2 && false == Check1)
	//{
	//	Check1 = true;
	//	CreateRenderer("Intro07_2.bmp", RenderPivot::CENTER, { -170, -20 });
	//}
	//
	//if (ActorTime_ >= 3 && false == Check2)
	//{
	//	Check2 = true;
	//	CreateRenderer("Intro07_3.bmp", RenderPivot::CENTER, { 200, -90 });
	//}
}

