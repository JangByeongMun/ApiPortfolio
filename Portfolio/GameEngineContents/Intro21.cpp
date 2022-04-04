#include "Intro21.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro21::Intro21() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro21::~Intro21() 
{
}

void Intro21::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("Intro21_1.bmp", RenderPivot::CENTER, { 20, 130 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -90, 40 });
	renderer->CreateAnimation("intro21_2.bmp", "intro21_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("intro21_2");
}

void Intro21::Update()
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

