#include "Intro17.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro17::Intro17()
	: IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, StartX()
	, CurrentX()
	, IsLeft(true)
{
}

Intro17::~Intro17() 
{
}

void Intro17::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("Intro17_1.bmp", RenderPivot::CENTER, { 0, 0 });

	float4 StartPos = {90, 180};
	StartX = StartPos.x;
	CurrentX = StartPos.x;
	IsaacRenderer_ = CreateRenderer("Intro17_2.bmp", RenderPivot::CENTER, StartPos);
}

void Intro17::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (IsLeft)
	{
		CurrentX -= 100.0f * GameEngineTime::GetDeltaTime();
		IsaacRenderer_->SetPivot({ CurrentX, 180 });
	
		if (StartX - 3.0f >= CurrentX)
		{
			IsLeft = !IsLeft;
		}
	}
	else
	{
		CurrentX += 100.0f * GameEngineTime::GetDeltaTime();
		IsaacRenderer_->SetPivot({ CurrentX, 180 });
	
		if (CurrentX >= StartX + 3.0f)
		{
			IsLeft = !IsLeft;
		}
	}
}

