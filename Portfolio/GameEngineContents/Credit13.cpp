#include "Credit13.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include "EndingLevel.h"

Credit13::Credit13() 
	: BookRenderer_(nullptr)
	, ActorTime_(0.0f)
{
}

Credit13::~Credit13() 
{
}

void Credit13::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 50 });
	renderer->CreateAnimation("epilogue13_1.bmp", "epilogue13_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue13_1");

	BookRenderer_ = CreateRenderer(RenderPivot::CENTER, { -130, -160 });
	BookRenderer_->CreateAnimation("epilogue13_2.bmp", "epilogue13_2", 0, 1, 0.3f, false);
	BookRenderer_->ChangeAnimation("epilogue13_2");
}

void Credit13::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();


	if (ActorTime_ >= 1.0f)
	{
		//Off();
		//((EndingLevel*)GetLevel())->ChangeEndingCredit(13);
	}
	else if (ActorTime_ >= 0.3f)
	{
		BookRenderer_->SetPivot(float4(-130, -160) + float4(-1000, -1000) * (ActorTime_ - 0.3f));
	}
}