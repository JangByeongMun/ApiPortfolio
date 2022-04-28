#include "Stone.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "HeartItem.h"

Stone::Stone() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, StoneType_(0)
{
}

Stone::~Stone() 
{
}

void Stone::BombStone()
{
	switch (StoneType_)
	{
	case 0: // 일반 돌
		Renderer_->SetIndex(3);
		break;
	case 1: // 검은 돌
		Renderer_->SetIndex(7);
		MakeRandomItemToBlackStone();
		break;
	case 2: // 항아리
		Renderer_->SetIndex(7);
		break;
	default:
		break;
	}

	Collision_->Off();
}

void Stone::Create(int _StonType)
{
	StoneType_ = _StonType;
	Renderer_ = CreateRenderer("rocks_basement.bmp");

	switch (StoneType_)
	{
	case 0: // 일반 돌
		Renderer_->SetIndex(GameEngineRandom::MainRandom->RandomInt(0, 2));
		break;
	case 1: // 검은 돌
		Renderer_->SetIndex(5);
		break;
	case 2: // 항아리
	{
		int RandomInt = (GameEngineRandom::MainRandom->RandomInt(0, 2));
		Renderer_->SetIndex(6 + (4 * RandomInt));
		break;
	}
	default:
		break;
	}
	Collision_ = CreateCollision("Stone", { 60, 65 });
}

void Stone::MakeRandomItemToBlackStone()
{
	float RandomFloat = GameEngineRandom::MainRandom->RandomFloat(0, 1);
	if (0.0f <= RandomFloat && RandomFloat < 0.6f)
	{
		HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
		TmpHeart->SetPosition(GetPosition());
		TmpHeart->Setting(HeartType::Soul);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.7f)
	{
		{
			HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
			TmpHeart->SetPosition(GetPosition());
			TmpHeart->Setting(HeartType::Soul);
			TmpHeart->AddRanomDir(-5, 5);
		}
		{
			HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
			TmpHeart->SetPosition(GetPosition());
			TmpHeart->Setting(HeartType::Soul);
			TmpHeart->AddRanomDir(-5, 5);
		}
	}
}