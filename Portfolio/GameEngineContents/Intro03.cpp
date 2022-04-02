#include "Intro03.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro03::Intro03() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro03::~Intro03() 
{
}

void Intro03::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("Intro03_1.bmp", "Intro03_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro03_1");
}

void Intro03::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();
}

