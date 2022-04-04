#include "Intro19.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro19::Intro19() 
	: IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
{
}

Intro19::~Intro19() 
{
}

void Intro19::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("Intro19_1.bmp", RenderPivot::CENTER, { 0, 70 });

	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { -160, -30 });
	IsaacRenderer_->CreateAnimation("Intro19_2.bmp", "Intro19_2", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro19_3.bmp", "Intro19_3", 0, 1, 0.1f, true);
	IsaacRenderer_->ChangeAnimation("Intro19_2");
}

void Intro19::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		IsaacRenderer_->ChangeAnimation("Intro19_3");
		IsaacRenderer_->SetPivot({ -180, -30 });
	}
	
	//if (ActorTime_ >= 3 && false == Check2)
	//{
	//	Check2 = true;
	//}
}

