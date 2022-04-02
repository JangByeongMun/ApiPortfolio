#include "Intro06.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro06::Intro06() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro06::~Intro06() 
{
}

void Intro06::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("Intro06_1.bmp", "Intro06_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro06_1");
}

void Intro06::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		CreateRenderer("Intro06_2.bmp", RenderPivot::CENTER, { -170, -20 });
	}

	if (ActorTime_ >= 3 && false == Check2)
	{
		Check2 = true;
		CreateRenderer("Intro06_3.bmp", RenderPivot::CENTER, { 200, -90 });
	}
}

