#include "Credit15.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

Credit15::Credit15()
	:IsaacRenderer_(nullptr)
	, ActorTime_(0.0f)
{
}

Credit15::~Credit15() 
{
}

void Credit15::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	
	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, 150 });
	renderer->CreateAnimation("epilogue15_1.bmp", "epilogue15_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue15_1");
	

	IsaacRenderer_ = CreateRenderer(RenderPivot::CENTER, { -230, 50 });
	IsaacRenderer_->CreateAnimation("epilogue15_2.bmp", "epilogue15_2", 0, 1, 0.1f, true);
	IsaacRenderer_->CreateAnimation("epilogue15_3.bmp", "epilogue15_3", 0, 1, 0.1f, true);
	IsaacRenderer_->ChangeAnimation("epilogue15_2");
}

void Credit15::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (ActorTime_ >= 2.2f)
	{
		CreateRenderer("epilogue15_4.bmp", RenderPivot::CENTER, { -40, 120 });
	}
	else if (ActorTime_ >= 2.0f)
	{
		IsaacRenderer_->SetPivot(float4(-230, 50) + float4(900, -350) * (ActorTime_ - 2.0f));
		IsaacRenderer_->ChangeAnimation("epilogue15_3");
	}
}

