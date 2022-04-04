#include "Intro04.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Intro04::Intro04() 
	: ActorTime_(0)
{
}

Intro04::~Intro04() 
{
}

void Intro04::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	//CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, { 0, 0 });

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 50 });
	renderer->CreateAnimation("Intro04_1.bmp", "Intro04_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("Intro04_1");
}
