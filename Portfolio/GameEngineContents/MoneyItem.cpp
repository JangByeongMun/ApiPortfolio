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
		Renderer_->CreateAnimation("pickup_002_coin_1.bmp", "pickup_002_coin_1", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coin_2.bmp", "pickup_002_coin_2", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coin_3.bmp", "pickup_002_coin_3", 0, 8, 0.05f, false);
		Renderer_->ChangeAnimation("pickup_002_coin_2");

		ShadowRenderer_->CreateAnimation("pickup_002_coin_1_Shadow.bmp", "pickup_002_coin_1_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coin_2_Shadow.bmp", "pickup_002_coin_2_Shadow", 0, 7, 0.05f, true);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		ShadowRenderer_->ChangeAnimation("pickup_002_coin_2_Shadow");
		break;


	case MoneyType::Black:
		Renderer_->CreateAnimation("pickup_002_coinblack_1.bmp", "pickup_002_coinblack_1", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coinblack_2.bmp", "pickup_002_coinblack_2", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coinblack_3.bmp", "pickup_002_coinblack_3", 0, 6, 0.05f, false);
		Renderer_->ChangeAnimation("pickup_002_coinblack_2");

		ShadowRenderer_->CreateAnimation("pickup_002_coinblack_1_Shadow.bmp", "pickup_002_coinblack_1_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coinblack_2_Shadow.bmp", "pickup_002_coinblack_2_Shadow", 0, 7, 0.05f, true);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		ShadowRenderer_->ChangeAnimation("pickup_002_coinblack_2_Shadow");
		break;


	case MoneyType::Silver:
		Renderer_->CreateAnimation("pickup_002_coinsilver_1.bmp", "pickup_002_coinsilver_1", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coinsilver_2.bmp", "pickup_002_coinsilver_2", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coinsilver_3.bmp", "pickup_002_coinsilver_3", 0, 6, 0.05f, false);
		Renderer_->ChangeAnimation("pickup_002_coinsilver_2");

		ShadowRenderer_->CreateAnimation("pickup_002_coinsilver_1_Shadow.bmp", "pickup_002_coinsilver_1_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coinsilver_2_Shadow.bmp", "pickup_002_coinsilver_2_Shadow", 0, 7, 0.05f, true);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		ShadowRenderer_->ChangeAnimation("pickup_002_coinsilver_2_Shadow");
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

	

	/////// 충돌
	if (true == Collision_->IsUpdate() && true == Collision_->CollisionCheckRect("Player"))
	{
		switch (Type_)
		{
		case MoneyType::None:
			break;
		case MoneyType::Normal:
			Player::MainPlayer->AddItem(ItemType::Money);
			Renderer_->ChangeAnimation("pickup_002_coin_3");
			break;
		case MoneyType::Black:
			Player::MainPlayer->AddItem(ItemType::MoneyBlack);
			Renderer_->ChangeAnimation("pickup_002_coinblack_3");
			break;
		case MoneyType::Silver:
			Player::MainPlayer->AddItem(ItemType::MoneySilver);
			Renderer_->ChangeAnimation("pickup_002_coinsilver_3");
			break;
		default:
			break;
		}

		ShadowRenderer_->ChangeAnimation("None");
		Collision_->Off();
	}

	/////// 애니메이션
	if (false == Renderer_->IsEndAnimation())
	{
		return;
	}

	if (Renderer_->CurrentAnimation() == Renderer_->FindAnimation("pickup_002_coin_2")) // Normal
	{
		Renderer_->ChangeAnimation("pickup_002_coin_1");
		ShadowRenderer_->ChangeAnimation("pickup_002_coin_1_Shadow");
	}
	else if (Renderer_->CurrentAnimation() == Renderer_->FindAnimation("pickup_002_coinblack_2")) // Black
	{
		Renderer_->ChangeAnimation("pickup_002_coinblack_1");
		ShadowRenderer_->ChangeAnimation("pickup_002_coinblack_1_Shadow");
	}
	else if (Renderer_->CurrentAnimation() == Renderer_->FindAnimation("pickup_002_coinsilver_2")) // Silver
	{
		Renderer_->ChangeAnimation("pickup_002_coinsilver_1");
		ShadowRenderer_->ChangeAnimation("pickup_002_coinsilver_1_Shadow");
	}

	// 먹힌후 애니메이션 실행하고 삭제
	if (
		Renderer_->CurrentAnimation() == Renderer_->FindAnimation("pickup_002_coin_3")
		||
		Renderer_->CurrentAnimation() == Renderer_->FindAnimation("pickup_002_coinblack_3")
		||
		Renderer_->CurrentAnimation() == Renderer_->FindAnimation("pickup_002_coinsilver_3")
		)
	{
		Death();
	}
}
