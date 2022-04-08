#include "Credit11.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

Credit11::Credit11() 
	: BookRenderer_(nullptr)
	, ActorTime_(0.0f)
{
}

Credit11::~Credit11() 
{
}

void Credit11::Start()
{
	ActorTime_ = 0.0f;
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("epilogue11_1.bmp", RenderPivot::CENTER, {20, 50});

	BookRenderer_ = CreateRenderer(RenderPivot::CENTER, {-80, -25});
	BookRenderer_->CreateAnimation("epilogue11_2.bmp", "epilogue11_2", 0, 1, 0.1f, true);
	BookRenderer_->CreateAnimation("epilogue11_3.bmp", "epilogue11_3", 0, 1, 0.1f, true);
	BookRenderer_->CreateAnimation("epilogue11_4.bmp", "epilogue11_4", 0, 0, 0.1f, true);
	BookRenderer_->ChangeAnimation("epilogue11_2");
}

void Credit11::Update()
{
	ActorTime_ += GameEngineTime::GetDeltaTime();

	if (2 <= ActorTime_)
	{
		BookRenderer_->ChangeAnimation("epilogue11_4");
	}
	else if (1.95 <= ActorTime_)
	{
		BookRenderer_->SetPivot(float4(-130, -80) + float4(-3000, 1000) * (ActorTime_ - 3));
	}
	else if (0.95 <= ActorTime_)
	{
		BookRenderer_->SetPivot({-130, -80});
		BookRenderer_->ChangeAnimation("epilogue11_3");
	}
}