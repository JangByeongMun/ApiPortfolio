#include "Fire.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include "PlayerHP.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "MoneyItem.h"
#include "HeartItem.h"

Fire::Fire() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, FireHp_(10.0f)
{
}

Fire::~Fire() 
{
}

void Fire::AddFireHP(float _Value)
{
	FireHp_ += _Value;

	if (FireHp_ >= 10.0f)
	{
		Renderer_->SetScale(float4(144.0f, 144.0f));
	}
	else if (FireHp_ >= 6.0f)
	{
		Renderer_->SetScale(float4(144.0f, 144.0f) * 0.7f);
	}
	else
	{
		Renderer_->SetScale(float4(144.0f, 144.0f) * 0.5f);
	}


	if (FireHp_ <= 0.5f)
	{
		FireHp_ = 0.0f;

		for (int i = 0; i < FirePlaceRenderer_.size(); i++)
		{
			FirePlaceRenderer_[i]->ChangeAnimation("grid_fireplace_Off");
		}

		RandomDrop();
		Renderer_->Off();
		Collision_->Off();
	}
}

void Fire::Start()
{
	{
		GameEngineRenderer* Renderer = CreateRenderer(RenderPivot::CENTER);
		Renderer->CreateAnimation("grid_fireplace.bmp", "grid_fireplace_Off", 0, 0, 0, false);
		Renderer->CreateAnimation("grid_fireplace.bmp", "grid_fireplace_On", 1, 3, 0.1f, true);
		Renderer->ChangeAnimation("grid_fireplace_On");
		Renderer->SetPivot({ 0, 20 });

		FirePlaceRenderer_.push_back(Renderer);
	}

	{
		GameEngineRenderer* Renderer = CreateRenderer(RenderPivot::CENTER);
		Renderer->CreateAnimation("grid_fireplace_Shadow.bmp", "grid_fireplace_Off", 0, 0, 0, false);
		Renderer->CreateAnimation("grid_fireplace_Shadow.bmp", "grid_fireplace_On", 1, 3, 0.1f, true);
		Renderer->ChangeAnimation("grid_fireplace_On");
		Renderer->SetPivot({ 0, 20 });
		Renderer->SetAlpha(100);

		FirePlaceRenderer_.push_back(Renderer);
	}

	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);
	Renderer_->CreateAnimation("effect_005_fire.bmp", "effect_005_fire", 0, 5, 0.1f, true);
	Renderer_->ChangeAnimation("effect_005_fire");
	Renderer_->SetPivot({ 0, -20 });
	Renderer_->SetAlpha(150);

	Collision_ = CreateCollision("Fire", {60, 45});
}

void Fire::Update()
{
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->GetPlayerHP()->MinusHearts(true);
	}
}

void Fire::RandomDrop()
{
	float RandomFloat = GameEngineRandom::MainRandom->RandomFloat(0.0f, 1.0f);
	if (0.0f <= RandomFloat && RandomFloat < 0.3f)
	{
		HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
		TmpHeart->SetPosition(GetPosition());
		TmpHeart->Setting(HeartType::RedHalf);
	}
	else if (0.3f <= RandomFloat && RandomFloat < 0.6f)
	{
		HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
		TmpHeart->SetPosition(GetPosition());
		TmpHeart->Setting(HeartType::Red);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.9f)
	{
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Normal);
		TmpObject->SetPosition(GetPosition());
	}
}

