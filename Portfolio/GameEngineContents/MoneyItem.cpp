#include "MoneyItem.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

MoneyItem::MoneyItem()
	: Type_(MoneyType::None)
	, Renderer_(nullptr)
	, ShadowRenderer_(nullptr)
	, State_(MoneyState::Default)
{
}

MoneyItem::~MoneyItem() 
{
}

void MoneyItem::SetType(MoneyType _Type, bool _IsSoundOn)
{
	Type_ = _Type;
	if (true == _IsSoundOn)
	{
		GameEngineSound::SoundPlayOneShotWithVolume("penny drop 1.wav", 0, 0.015f * Option_SFX);
	}

	Renderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 }, static_cast<int>(ORDER::PLAYER));
	ShadowRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 }, static_cast<int>(ORDER::PLAYER));
	Collision_ = CreateCollision("Item", {50, 50});

	switch (_Type)
	{
	case MoneyType::None:
		break;
	case MoneyType::Normal:
		Renderer_->CreateAnimation("pickup_002_coin_1.bmp", "coin_Idle", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coin_2.bmp", "coin_Appear", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coin_3.bmp", "coin_Destroy", 0, 8, 0.05f, false);

		ShadowRenderer_->CreateAnimation("pickup_002_coin_1_Shadow.bmp", "coin_Idle_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coin_2_Shadow.bmp", "coin_Appear_Shadow", 0, 7, 0.05f, false);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		break;


	case MoneyType::Black:
		Renderer_->CreateAnimation("pickup_002_coinblack_1.bmp", "coin_Idle", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coinblack_2.bmp", "coin_Appear", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coinblack_3.bmp", "coin_Destroy", 0, 6, 0.05f, false);

		ShadowRenderer_->CreateAnimation("pickup_002_coinblack_1_Shadow.bmp", "coin_Idle_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coinblack_2_Shadow.bmp", "coin_Appear_Shadow", 0, 7, 0.05f, false);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		break;


	case MoneyType::Silver:
		Renderer_->CreateAnimation("pickup_002_coinsilver_1.bmp", "coin_Idle", 0, 5, 0.1f, true);
		Renderer_->CreateAnimation("pickup_002_coinsilver_2.bmp", "coin_Appear", 0, 7, 0.05f, false);
		Renderer_->CreateAnimation("pickup_002_coinsilver_3.bmp", "coin_Destroy", 0, 6, 0.05f, false);

		ShadowRenderer_->CreateAnimation("pickup_002_coinsilver_1_Shadow.bmp", "coin_Idle_Shadow", 0, 5, 0.05f, true);
		ShadowRenderer_->CreateAnimation("pickup_002_coinsilver_2_Shadow.bmp", "coin_Appear_Shadow", 0, 7, 0.05f, false);
		ShadowRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
		break;


	default:
		break;
	}
	ChangeState(MoneyState::Appear);
}
void MoneyItem::Update()
{
	SetObjectMove();
	StateUpdate();
}

//////////////////// FSM
void MoneyItem::ChangeState(MoneyState _State)
{
	if (State_ == _State)
	{
		return;
	}

	State_ = _State;
	switch (State_)
	{
	case MoneyState::Appear:
		AppearStart();
		break;
	case MoneyState::Idle:
		IdleStart();
		break;
	case MoneyState::Destroy:
		DestroyStart();
		break;
	default:
		break;
	}
}
void MoneyItem::StateUpdate()
{
	switch (State_)
	{
	case MoneyState::Appear:
		AppearUpdate();
		break;
	case MoneyState::Idle:
		IdleUpdate();
		break;
	case MoneyState::Destroy:
		DestroyUpdate();
		break;
	default:
		break;
	}
}

void MoneyItem::AppearStart()
{
	Renderer_->ChangeAnimation("coin_Appear");
	ShadowRenderer_->ChangeAnimation("coin_Appear_Shadow");
}
void MoneyItem::IdleStart()
{
	Renderer_->ChangeAnimation("coin_Idle");
	ShadowRenderer_->ChangeAnimation("coin_Idle_Shadow");
}
void MoneyItem::DestroyStart()
{
	Renderer_->ChangeAnimation("coin_Destroy");
	ShadowRenderer_->ChangeAnimation("None");
}


void MoneyItem::AppearUpdate()
{
	if (Renderer_->IsEndAnimation())
	{
		ChangeState(MoneyState::Idle);
	}
}
void MoneyItem::IdleUpdate()
{
	if (true == Collision_->CollisionCheckRect("Player"))
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
		Collision_->Off();
		ChangeState(MoneyState::Destroy);
	}
}
void MoneyItem::DestroyUpdate()
{
	if (Renderer_->IsEndAnimation())
	{
		GameEngineSound::SoundPlayOneShotWithVolume("penny pickup 1.wav", 0, 0.015f * Option_SFX);
		Off();
	}
}
