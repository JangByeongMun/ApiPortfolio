#include "RandomBlood.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineRenderer.h>

RandomBlood::RandomBlood() 
	: Renderer_(nullptr)
	, Dir_()
{
}

RandomBlood::~RandomBlood() 
{
}

void RandomBlood::Start()
{
	int RandomImage = GameEngineRandom::MainRandom->RandomInt(0, 1);
	int RandomAlpha = GameEngineRandom::MainRandom->RandomInt(50, 200);
	if (RandomImage == 0)
	{
		int RandomIndex = GameEngineRandom::MainRandom->RandomInt(0, 15);
		GameEngineRenderer* TmpRenderer_ = CreateRenderer("effect_030_bloodgibs.bmp");
		TmpRenderer_->SetIndex(RandomIndex);
		TmpRenderer_->SetAlpha(RandomAlpha);
	}
	else
	{
		int RandomIndex = GameEngineRandom::MainRandom->RandomInt(0, 16);
		GameEngineRenderer* TmpRenderer_ = CreateRenderer("effect_032_bloodstains.bmp");
		TmpRenderer_->SetIndex(RandomIndex);
		TmpRenderer_->SetAlpha(RandomAlpha);
	}

	Dir_ = float4(GameEngineRandom::MainRandom->RandomFloat(-1, 1) * 2.0f, GameEngineRandom::MainRandom->RandomFloat(-1, 1) * 2.0f);
}

void RandomBlood::Update()
{
	if (false == Dir_.IsZero2D())
	{
		Dir_ += -Dir_ * GameEngineTime::GetDeltaTime() * 10;

		if (0.05f >= Dir_.Len2D())
		{
			Dir_ = float4::ZERO;
		}

		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 300);
	}
}