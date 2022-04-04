#include "Intro06.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro06::Intro06() 
	: FaceRenderer_(nullptr)
	, ActorTime_(0)
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
	
	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 20 });
		renderer->CreateAnimation("Intro06_1.bmp", "Intro06_1", 0, 1, 0.4f, true);
		renderer->ChangeAnimation("Intro06_1");
	}

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, -230 });
		renderer->CreateAnimation("Intro06_2.bmp", "Intro06_2", 0, 1, 0.2f, true);
		renderer->ChangeAnimation("Intro06_2"); 
	}

	FaceRenderer_ = CreateRenderer("intro06_4.bmp", RenderPivot::CENTER, { 30, -40 });
}

void Intro06::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;

		FaceRenderer_->CreateAnimation("Intro06_3.bmp", "Intro06_3", 0, 1, 0.2f, true);
		FaceRenderer_->ChangeAnimation("Intro06_3");
	}

	//if (ActorTime_ >= 3 && false == Check2)
	//{
	//	Check2 = true;
	//	//CreateRenderer("Intro06_3.bmp", RenderPivot::CENTER, { 200, -90 });
	//}
}

