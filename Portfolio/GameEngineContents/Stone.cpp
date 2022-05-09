#include "Stone.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "HeartItem.h"
#include "ContentsEnum.h"
#include "ContentsGlobal.h"
#include <GameEngineBase/GameEngineSound.h>

Stone::Stone() 
	: Renderer_(nullptr)
	, ShadowRenderer_(nullptr)
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
		ShadowRenderer_->SetIndex(3);
		break;
	case 1: // 검은 돌
		Renderer_->SetIndex(7);
		ShadowRenderer_->SetIndex(7);
		MakeRandomItemToBlackStone();
		break;
	case 2: // 항아리
		Renderer_->SetIndex(7);
		ShadowRenderer_->SetIndex(7);
		break;
	default:
		break;
	}

	std::string TmpName = "rock crumble";
	TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(1, 3)) + ".wav";
	GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 0.1f * Option_SFX);

	Renderer_->SetOrder(static_cast<int>(ORDER::BACKGROUND));
	ShadowRenderer_->SetOrder(static_cast<int>(ORDER::BACKGROUND));
	Collision_->Off();
}

void Stone::Create(int _StonType)
{
	StoneType_ = _StonType;
	std::string TmpName = "";
	switch (CurrentFloor)
	{
	case 1:
		TmpName = "rocks_basement";
		break;
	case 2:
		TmpName = "rocks_caves";
		break;
	case 3:
		TmpName = "rocks_depths";
		break;
	default:
		break;
	}
	Renderer_ = CreateRenderer(TmpName + ".bmp", static_cast<int>(ORDER::PLAYER));
	ShadowRenderer_ = CreateRenderer(TmpName + "_Shadow.bmp", static_cast<int>(ORDER::PLAYER));
	ShadowRenderer_->SetAlpha(100);

	switch (StoneType_)
	{
	case 0: // 일반 돌
	{
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 2);
		Renderer_->SetIndex(RandomInt);
		ShadowRenderer_->SetIndex(RandomInt);
		break;
	}
	case 1: // 검은 돌
		Renderer_->SetIndex(5);
		ShadowRenderer_->SetIndex(5);
		break;
	case 2: // 항아리
	{
		int RandomInt = (GameEngineRandom::MainRandom->RandomInt(0, 2));
		Renderer_->SetIndex(6 + (4 * RandomInt));
		ShadowRenderer_->SetIndex(6 + (4 * RandomInt));
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