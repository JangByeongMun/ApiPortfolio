#include "MoneyItem.h"
#include "Player.h"

MoneyItem::MoneyItem()
	: Type_(MoneyType::None)
	, Renderer_(nullptr)
	, ShadowRenderer_(nullptr)
{
}

MoneyItem::~MoneyItem() 
{
}

void MoneyItem::SetType(MoneyType _Type)
{
	Type_ = _Type;
	Renderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 });
	ShadowRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 });

	switch (_Type)
	{
	case MoneyType::None:
		break;
	case MoneyType::Normal:
		Renderer_->CreateAnimation("pickup_002_coin_1.bmp", "coin_Idle", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coin_2.bmp", "coin_Appear", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coin_3.bmp", "coin_Destroy", 0, 8, 0.05f, false);
		Renderer_->ChangeAnimation("coin_Appear");

		ShadowRenderer_->CreateAnimation("pickup_002_coin_1_Shadow.bmp", "coin_Idle_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coin_2_Shadow.bmp", "coin_Appear_Shadow", 0, 7, 0.05f, true);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		ShadowRenderer_->ChangeAnimation("coin_Appear_Shadow");
		break;


	case MoneyType::Black:
		Renderer_->CreateAnimation("pickup_002_coinblack_1.bmp", "coin_Idle", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coinblack_2.bmp", "coin_Appear", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coinblack_3.bmp", "coin_Destroy", 0, 6, 0.05f, false);
		Renderer_->ChangeAnimation("coin_Appear");

		ShadowRenderer_->CreateAnimation("pickup_002_coinblack_1_Shadow.bmp", "coin_Idle_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coinblack_2_Shadow.bmp", "coin_Appear_Shadow", 0, 7, 0.05f, true);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		ShadowRenderer_->ChangeAnimation("coin_Appear_Shadow");
		break;


	case MoneyType::Silver:
		Renderer_->CreateAnimation("pickup_002_coinsilver_1.bmp", "coin_Idle", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coinsilver_2.bmp", "coin_Appear", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coinsilver_3.bmp", "coin_Destroy", 0, 6, 0.05f, false);
		Renderer_->ChangeAnimation("coin_Appear");

		ShadowRenderer_->CreateAnimation("pickup_002_coinsilver_1_Shadow.bmp", "coin_Idle_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coinsilver_2_Shadow.bmp", "coin_Appear_Shadow", 0, 7, 0.05f, true);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		ShadowRenderer_->ChangeAnimation("coin_Appear_Shadow");
		break;


	default:
		break;
	}

	Collision_ = CreateCollision("Item", { 60, 60 });
}

void MoneyItem::Update()
{
	SetObjectMove();

	if (StartTimer_ < 0.2f)
	{
		return;
	}

	if (nullptr == Collision_ || nullptr == Renderer_)
	{
		return;
	}

	/////// 충돌
	if (true == Collision_->IsUpdate() && true == Renderer_->IsUpdate() && true == Collision_->CollisionCheckRect("Player"))
	{
		switch (Type_)
		{
		case MoneyType::None:
			break;
		case MoneyType::Normal:
			Player::MainPlayer->AddItem(ItemType::Money);
			break;
		case MoneyType::Black:
			Player::MainPlayer->AddItem(ItemType::MoneyBlack);
			break;
		case MoneyType::Silver:
			Player::MainPlayer->AddItem(ItemType::MoneySilver);
			break;
		default:
			break;
		}
		Renderer_->ChangeAnimation("coin_Destroy");
		ShadowRenderer_->ChangeAnimation("None");
		Collision_->Off();
	}

	/////// 애니메이션
	if (true == Renderer_->IsEndAnimation())
	{
		if (Renderer_->CurrentAnimation() == Renderer_->FindAnimation("coin_Appear"))
		{
			Renderer_->ChangeAnimation("coin_Idle");
			ShadowRenderer_->ChangeAnimation("coin_Idle_Shadow");
		}

		// 먹힌후 애니메이션 실행하고 삭제
		if (Renderer_->CurrentAnimation() == Renderer_->FindAnimation("coin_Destroy"))
		{
			Renderer_ = nullptr;
			ShadowRenderer_ = nullptr;
			Collision_ = nullptr;
			Death(1.0f);
		}
	}
}
