#include "Credit12.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include "EndingLevel.h"

Credit12::Credit12()
	: BookRenderer_(nullptr)
	, ActorTime_(0.0f)
{
}

Credit12::~Credit12() 
{
}

void Credit12::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 40 });
	renderer->CreateAnimation("epilogue12_1.bmp", "epilogue12_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue12_1");

	BookRenderer_ = CreateRenderer(RenderPivot::CENTER, {-20, -270});
	BookRenderer_->CreateAnimation("epilogue12_2.bmp", "epilogue12_2", 0, 1, 0.1f, true);
	BookRenderer_->ChangeAnimation("epilogue12_2");
}

void Credit12::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2.0f)
	{
		//Off();
		//((EndingLevel*)GetLevel())->ChangeEndingCredit(12);
	}
	else if (ActorTime_ >= 1.9f)
	{
		BookRenderer_->SetPivot(float4(-20, -270) + float4(0, 500) * (ActorTime_ - 2));
	}
}

