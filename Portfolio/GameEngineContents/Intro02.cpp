#include "Intro02.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro02::Intro02() 
	: ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro02::~Intro02() 
{
}

void Intro02::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer->CreateAnimation("intro02_1.bmp", "intro02_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("intro02_1");
}

void Intro02::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();
}