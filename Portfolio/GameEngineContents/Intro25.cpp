#include "Intro25.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>

Intro25::Intro25() 
	: IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro25::~Intro25() 
{
}

void Intro25::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("Intro25_2.bmp", RenderPivot::CENTER, { -20, 100 });

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 50 });
		renderer->CreateAnimation("Intro25_1.bmp", "Intro25_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("Intro25_1");
	}
	
	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { -40, 90 });
	IsaacRenderer_->CreateAnimation("Intro25_3.bmp", "Intro25_3", 0, 0, 0.1f, false);
	IsaacRenderer_->CreateAnimation("Intro25_4.bmp", "Intro25_4", 0, 1, 0.1f, true);
	IsaacRenderer_->ChangeAnimation("Intro25_3");
}

void Intro25::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ <= 0.2f)
	{
		IsaacRenderer_->SetPivot({ -40, 90 + (200 * ActorTime_) });
	}

	if (ActorTime_ >= 0.2f && false == Check1)
	{
		Check1 = true;
		IsaacRenderer_->ChangeAnimation("Intro25_4");
	}
	
	if (ActorTime_ >= 3 && false == Check2)
	{
		Check2 = true;
		GameEngine::GetInst().ChangeLevel("Menu");
	}
}

