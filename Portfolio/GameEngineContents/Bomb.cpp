#include "Bomb.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "PlayLevel.h"
#include "Projectile.h"
#include "Stone.h"
#include "Monster.h"
#include "Player.h"
#include "PlayerUI.h"
#include "PlayerHP.h"
#include "Poop.h"
#include "Fire.h"
#include "ItemBase.h"
#include "ShopKeeper.h"
#include "ContentsGlobal.h"
#include "BoomEffect.h"

Bomb::Bomb() 
	: Renderer_(nullptr)
	, Timer_ (0.0f)
	, BombTime_(2.0f)
	, IsExplode(false)
{
}

Bomb::~Bomb() 
{
}

void Bomb::Start()
{
	Collision_ = CreateCollision("Bomb", { 80, 80 }, { 0, 0 });
	Renderer_ = CreateRenderer(RenderPivot::CENTER, GetPosition());
	Renderer_->CreateAnimation("pickup_016_bomb_One.bmp", "pickup_016_bomb_One", 0, 2, 0.2f, true);
	Renderer_->ChangeAnimation("pickup_016_bomb_One");
}

void Bomb::Update()
{
	if (true == IsExplode)
	{
		return;
	}

	Timer_ += GameEngineTime::GetDeltaTime();
	BompAnimation();
	
	std::vector<GameEngineCollision*> CollisionResult_;
	if (true == Collision_->CollisionResult("Projectile", CollisionResult_, CollisionType::Rect, CollisionType::Rect))
	{
		float4 MoveDir = { 0, 0 };
		for (int i = 0; i < CollisionResult_.size(); i++)
		{
			if (CollisionResult_[i] == nullptr)
			{
				continue;
			}

			Projectile* TmpProjectile = static_cast<Projectile*>(CollisionResult_[i]->GetActor());
			TmpProjectile->DestroyProjectile();

			MoveDir += (GetPosition() - CollisionResult_[i]->GetCollisionPos());
			MoveDir.Normal2D();
			AddDir(MoveDir * 2.0f);
		}

		SetMove(MoveDir * 0.1f);
	}
	CollisionResult_.clear();

	SetObjectMove();


	if (Timer_ >= BombTime_)
	{
		Boom();
	}
}

void Bomb::BompAnimation()
{
	if (Timer_ <= 0.25f)
	{
		Renderer_->SetScale({ 86, 106 });
	}
	else if (Timer_ <= 0.5f)
	{
		Renderer_->SetScale({ 106, 86 });
	}
	else if (Timer_ <= 0.75f)
	{
		Renderer_->SetScale({ 86, 106 });
	}
	else if (Timer_ <= 1.0f)
	{
		Renderer_->SetScale({ 106, 86 });
	}

	else if (Timer_ <= 1.125f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 1.25f)
	{
		Renderer_->SetScale({ 126, 66 });
	}
	else if (Timer_ <= 1.375f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 1.5f)
	{
		Renderer_->SetScale({ 126, 66 });
	}

	else if (Timer_ <= 1.625f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 1.75f)
	{
		Renderer_->SetScale({ 126, 66 });
	}
	else if (Timer_ <= 1.875f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 2.0f)
	{
		Renderer_->SetScale({ 126, 66 });
	}
}

void Bomb::Boom()
{
	IsExplode = true;
	GetLevel()->CreateActor<BoomEffect>()->Setting(GetPosition());

	Off();
	Death(1.0f);
}
