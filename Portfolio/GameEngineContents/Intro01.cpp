#include "Intro01.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro01::Intro01() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro01::~Intro01() 
{
}

void Intro01::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("intro01_1.bmp", "intro01_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("intro01_1");
}

void Intro01::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		CreateRenderer("intro01_2.bmp", RenderPivot::CENTER, { -170, -20 });
	}

	if (ActorTime_ >= 3 && false == Check2)
	{
		Check2 = true;
		CreateRenderer("intro01_3.bmp", RenderPivot::CENTER, { 200, -90 });
	}
}

