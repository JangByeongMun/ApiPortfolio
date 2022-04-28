#include "HeartItem.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "PlayerHP.h"

HeartItem::HeartItem() 
	: Type_(HeartType::Default)
	, Renderer_(nullptr)
{
}

HeartItem::~HeartItem() 
{
}

void HeartItem::Setting(HeartType _Type)
{
	Renderer_ = CreateRenderer("pickup_001_heart.bmp", static_cast<int>(ORDER::PLAYER));
	Collision_ = CreateCollision("Item", { 50, 50 });

	Type_ = _Type;
	switch (Type_)
	{
	case HeartType::Red:
		Renderer_->SetIndex(0);
		break;
	case HeartType::RedHalf:
		Renderer_->SetIndex(1);
		break;
	case HeartType::RedTwo:
		Renderer_->SetIndex(8);
		break;
	case HeartType::Soul:
		Renderer_->SetIndex(3);
		break;
	case HeartType::SoulHalf:
		Renderer_->SetIndex(4);
		break;
	case HeartType::Black:
		Renderer_->SetIndex(6);
		break;
	case HeartType::BlackHalf:
		Renderer_->SetIndex(7);
		break;
	default:
		break;
	}
}

void HeartItem::Update()
{
	SetObjectMove();

	PlayerHP* TmpHp = Player::MainPlayer->GetPlayerHP();
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		float4 TmpDir = GetPosition() - Player::MainPlayer->GetPosition();
		TmpDir.Normal2D();
		AddDir(TmpDir * 2.0f);

		switch (Type_)
		{
		case HeartType::Red:
			if (TmpHp->AddRedHp(false))
			{
				Death();
			}
			break;
		case HeartType::RedHalf:
			if (TmpHp->AddRedHp(true))
			{
				Death();
			}
			break;
		case HeartType::RedTwo:
			if (TmpHp->AddRedHp(false))
			{
				TmpHp->AddRedHp(false);
				Death();
			}
			break;
		case HeartType::Soul:
			if (TmpHp->AddHearts(HeartData::SoulHeart, false))
			{
				Death();
			}
			break;
		case HeartType::SoulHalf:
			if (TmpHp->AddHearts(HeartData::SoulHeart, true))
			{
				Death();
			}
			break;
		case HeartType::Black:
			if (TmpHp->AddHearts(HeartData::BlackHeart, false))
			{
				Death();
			}
			break;
		case HeartType::BlackHalf:
			if (TmpHp->AddHearts(HeartData::BlackHeart, true))
			{
				Death();
			}
			break;
		default:
			break;
		}
	}
}

