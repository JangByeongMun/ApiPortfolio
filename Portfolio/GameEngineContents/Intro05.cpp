#include "Intro05.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro05::Intro05() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro05::~Intro05() 
{
}

void Intro05::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("Intro05_1.bmp", "Intro05_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro05_1");
}

void Intro05::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		CreateRenderer("Intro05_2.bmp", RenderPivot::CENTER, { -170, -20 });
	}

	if (ActorTime_ >= 3 && false == Check2)
	{
		Check2 = true;
		CreateRenderer("Intro05_3.bmp", RenderPivot::CENTER, { 200, -90 });
	}
}

