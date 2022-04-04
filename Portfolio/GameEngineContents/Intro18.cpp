#include "Intro18.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro18::Intro18() 
	: IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
	, Check3(false)
	, Check4(false)
	, Check5(false)
	, StartX(0)
	, CurrentX(0)
	, IsLeft(true)
{
}

Intro18::~Intro18() 
{
}

void Intro18::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("Intro18_1.bmp", RenderPivot::CENTER, { 0, 0 });

	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { -20, 220 });
	IsaacRenderer_->CreateAnimation("Intro18_2.bmp", "Intro18_2", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro18_3.bmp", "Intro18_3", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro18_4.bmp", "Intro18_4", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro18_5.bmp", "Intro18_5", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro18_6.bmp", "Intro18_6", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("Intro18_7.bmp", "Intro18_7", 0, 0, 0.1f, false);
	IsaacRenderer_->CreateAnimation("None.bmp", "None", 0, 1, 0.1f, true);
	IsaacRenderer_->ChangeAnimation("Intro18_2");

	StartX = 0;
	CurrentX = 0;
}

void Intro18::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 0.5f && false == Check1)
	{
		Check1 = true;
		IsaacRenderer_->ChangeAnimation("Intro18_3");
		IsaacRenderer_->SetPivot({ 130, 240 });
	}
	
	if (ActorTime_ >= 1.0f && false == Check2)
	{
		Check2 = true;
		IsaacRenderer_->ChangeAnimation("Intro18_4");
		IsaacRenderer_->SetPivot({ -20, -40 });
	}

	if (ActorTime_ >= 1.5f && false == Check3)
	{
		Check3 = true;
		IsaacRenderer_->ChangeAnimation("Intro18_5");
		IsaacRenderer_->SetPivot({ -200, 100 });
	}

	if (ActorTime_ >= 2.0f && false == Check4)
	{
		Check4 = true;
		IsaacRenderer_->ChangeAnimation("Intro18_6");
		IsaacRenderer_->SetPivot({ -160, 250 });
	}

	if (ActorTime_ >= 2.5f && false == Check5)
	{
		Check5 = true;
		IsaacRenderer_->ChangeAnimation("Intro18_6");
		IsaacRenderer_->SetPivot({ -160, 250 });
	}

	if (ActorTime_ >= 3.0f)
	{
		IsaacRenderer_->ChangeAnimation("Intro18_7");

		if (IsLeft)
		{
			CurrentX -= 100.0f * GameEngineTime::GetDeltaTime();
			IsaacRenderer_->SetPivot({ CurrentX, 220 });

			if (StartX - 3.0f >= CurrentX)
			{
				IsLeft = !IsLeft;
			}
		}
		else
		{
			CurrentX += 100.0f * GameEngineTime::GetDeltaTime();
			IsaacRenderer_->SetPivot({ CurrentX, 220 });

			if (CurrentX >= StartX + 3.0f)
			{
				IsLeft = !IsLeft;
			}
		}
	}
}

