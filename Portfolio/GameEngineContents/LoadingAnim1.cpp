#include "LoadingAnim1.h"
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsEnum.h"

LoadingAnim1::LoadingAnim1() 
	: AnimTimer_(0.0f)
{
}

LoadingAnim1::~LoadingAnim1() 
{
}

void LoadingAnim1::Start()
{
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_1_1.bmp", static_cast<int>(ORDER::UI));
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_1_2.bmp", static_cast<int>(ORDER::UI));
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("nightmare_1_3.bmp", static_cast<int>(ORDER::UI));
		TmpRenderer->CreateAnimation("nightmare_1_3.bmp", "nightmare_1_3", 0, 1, 0.3f, true);
		TmpRenderer->ChangeAnimation("nightmare_1_3");
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}
}

void LoadingAnim1::Update()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ <= 0.5)
	{

	}
	else if (AnimTimer_ <= 1.0)
	{
		RendererVector_[0]->On();

		float4 LerpScale = float4::Lerp({ 305, 243 }, { 610, 486 }, (AnimTimer_ - 0.5f) * 3.0f);
		RendererVector_[0]->SetScale(LerpScale);
	}
	else if (AnimTimer_ <= 1.5)
	{
		RendererVector_[0]->Off();
		RendererVector_[1]->On();
		RendererVector_[2]->On();
	}
}

