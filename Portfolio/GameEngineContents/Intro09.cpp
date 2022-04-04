#include "Intro09.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro09::Intro09() 
	: IsaacRenderer_(nullptr)
	, ActorTime_(0)
	, Check1(false)
	, Check2(false)
	, Check3(false)
	, Check4(false)
{
}

Intro09::~Intro09() 
{
}

void Intro09::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	IsaacRenderer_->CreateAnimation("Intro09_1.bmp", "Intro09_1", 0, 1, 0.1f, true);
	//IsaacRenderer_->CreateAnimation("Intro09_2.bmp", "Intro09_2", 0, 1, 0.1f, true);
	//IsaacRenderer_->CreateAnimation("Intro09_3.bmp", "Intro09_3", 0, 1, 0.1f, true); 
	//IsaacRenderer_->CreateAnimation("Intro09_4.bmp", "Intro09_4", 0, 1, 0.1f, true);
	//IsaacRenderer_->CreateAnimation("Intro09_5.bmp", "Intro09_5", 0, 1, 0.1f, true);
	IsaacRenderer_->ChangeAnimation("Intro09_1");

	GameEngineRenderer* renderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
	renderer_->CreateAnimation("intro09_2.bmp", "intro09_2", 0, 1, 0.1f, true);
	renderer_->ChangeAnimation("intro09_2");
}

void Intro09::Update()
{
	/*ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2 && false == Check1)
	{
		Check1 = true;
		IsaacRenderer_->ChangeAnimation("Intro09_2");

		GameEngineRenderer* renderer_ = CreateRenderer(RenderPivot::CENTER, { 150, 0 });
		renderer_->CreateAnimation("intro09_6.bmp", "intro09_6", 0, 3, 0.1f, false);
		renderer_->ChangeAnimation("intro09_6");
	}
	
	if (ActorTime_ >= 4 && false == Check2)
	{
		Check2 = true;
		IsaacRenderer_->ChangeAnimation("Intro09_3");

		GameEngineRenderer* renderer_ = CreateRenderer(RenderPivot::CENTER, { -150, 0 });
		renderer_->CreateAnimation("intro09_7.bmp", "intro09_7", 0, 3, 0.1f, false);
		renderer_->ChangeAnimation("intro09_7");
	}

	if (ActorTime_ >= 5 && false == Check3)
	{
		Check3 = true;
		IsaacRenderer_->ChangeAnimation("Intro09_4");
	}

	if (ActorTime_ >= 6 && false == Check4)
	{
		Check4 = true;
		IsaacRenderer_->ChangeAnimation("Intro09_5");
	}*/
}

