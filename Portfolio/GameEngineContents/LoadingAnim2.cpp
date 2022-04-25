#include "LoadingAnim2.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>

LoadingAnim2::LoadingAnim2()
	: AnimTimer_(0.0f)
{
}

LoadingAnim2::~LoadingAnim2()
{
}

void LoadingAnim2::Start()
{
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_5_1.bmp", static_cast<int>(ORDER::UI));
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_5_2.bmp", static_cast<int>(ORDER::UI));
		TmpRenderer->SetPivot({ 30, 40 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_5_3.bmp", static_cast<int>(ORDER::UI));
		TmpRenderer->Off();
		TmpRenderer->SetPivot({70, 40});
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_5_4.bmp", static_cast<int>(ORDER::UI));
		TmpRenderer->Off();
		TmpRenderer->SetPivot({ 90, 80 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_5_6.bmp", static_cast<int>(ORDER::UI));
		TmpRenderer->Off();
		TmpRenderer->SetPivot({ -20, 80 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		BallRenderer_ = CreateRenderer("nightmare_5_7.bmp", static_cast<int>(ORDER::UI));
		BallRenderer_->SetPivot({ -30, 40 });
	}
}

void LoadingAnim2::Update()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ <= 0.25f)
	{
		float4 LerpScale = float4::Lerp({ -270, 20 }, { -30, 40 }, AnimTimer_ * 4.0f);
		BallRenderer_->SetPivot(LerpScale);
	}
	else if (AnimTimer_ <= 0.5f)
	{
		float4 LerpScale = float4::Lerp({ -30, 40 }, { -80, -100 }, (AnimTimer_ - 0.25f) * 4.0f);
		BallRenderer_->SetPivot(LerpScale);

		RendererVector_[0]->Off();
		RendererVector_[1]->On();
		RendererVector_[3]->On();
	}
	else if (AnimTimer_ <= 0.75f)
	{
		BallRenderer_->Off();
		RendererVector_[1]->Off();
		RendererVector_[2]->On();
	}
}

