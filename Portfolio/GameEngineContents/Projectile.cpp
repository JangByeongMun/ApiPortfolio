#include "Projectile.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PlayLevel.h"
#include "Player.h"
#include "RoomActor.h"
#include "RandomRoomManager.h"
#include "Monster.h"
#include "PlayerHP.h"
#include "Fire.h"
#include "Poop.h"

Projectile::Projectile() 
	: Collision_()
	, Type_(ProjectileType::PLAYER_BASIC)
	, Vec_({ 0, 0 })
	, Lifetime_(0)
	, CurrentTimer_(0)
	, Damage_(0)
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	Collision_ = CreateCollision("Projectile", { 30, 30 }, { 0, 0 });
}

void Projectile::Update()
{
	CurrentTimer_ += GameEngineTime::GetDeltaTime();

	if (Lifetime_ - CurrentTimer_ <= 0.3f)
	{
		Vec_ += {0, 600 * GameEngineTime::GetDeltaTime()};
	}

	// 설정한 시간이 지나면 삭제
	if (Lifetime_ - CurrentTimer_ <= 0.0f)
	{
		DestroyProjectile();
	}

	// 돌과 충돌했을때
	if (true == Collision_->CollisionCheckRect("Stone"))
	{
		DestroyProjectile();
	}

	// 불과 충돌했을때
	{
		std::vector<GameEngineCollision*> CollisionResult;
		if (true == Collision_->CollisionResultRect("Fire", CollisionResult))
		{
			for (int i = 0; i < CollisionResult.size(); i++)
			{
				Fire* TmpFire = dynamic_cast<Fire*>(CollisionResult[i]->GetActor());
				if (nullptr != TmpFire)
				{
					TmpFire->AddFireHP(-1 * Damage_);
					DestroyProjectile();
					break;
				}
			}
		}
	}

	// 똥과 충돌했을때
	{
		std::vector<GameEngineCollision*> CollisionResult;
		if (true == Collision_->CollisionResultRect("Poop", CollisionResult))
		{
			for (int i = 0; i < CollisionResult.size(); i++)
			{
				Poop* TmpPoop = dynamic_cast<Poop*>(CollisionResult[i]->GetActor());
				if (nullptr != TmpPoop)
				{
					TmpPoop->AddHp(-1 * Damage_);
					DestroyProjectile();
					break;
				}
			}
		}
	}

	// 플레이어의 눈물이면
	if (true == IsPlayerProjectile())
	{
		// 몬스터와 충돌했을때
		std::vector<GameEngineCollision*> CollisionResult;
		if (true == Collision_->CollisionResultRect("Monster", CollisionResult))
		{
			for (int i = 0; i < CollisionResult.size(); i++)
			{
				Monster* TmpMonster = dynamic_cast<Monster*>(CollisionResult[i]->GetActor());
				if (nullptr != TmpMonster)
				{
					TmpMonster->Damaged(Damage_);
					DestroyProjectile();
					break;
				}
			}
		}
	}

	// 적의 눈물이면
	if (false == IsPlayerProjectile())
	{
		std::vector<GameEngineCollision*> CollisionResult;
		if (true == Collision_->CollisionCheckRect("Player"))
		{
			Player::MainPlayer->GetPlayerHP()->AddRedHp(-1, true);
			DestroyProjectile();
		}
	}
	
	// 벽을 못넘어가도록 넘어가려고하면 삭제
	RoomActor* FindRoom = RandomRoomManager::GetInst()->GetCurrentRoom();
	float4 AddPivot = FindRoom->GetPosition() - GameEngineWindow::GetScale().Half();
	int Color = Player::MainPlayer->GetMapColImage()->GetImagePixel(GetPosition() - AddPivot);
	if (RGB(0, 0, 0) == Color)
	{
		DestroyProjectile();
	}

	SetMove(Vec_ * GameEngineTime::GetDeltaTime());
}

void Projectile::DestroyProjectile()
{
	PlayLevel* TmpLevel = static_cast<PlayLevel*>(GetLevel());

	if (true == IsPlayerProjectile())
	{
		GameEngineRenderer* TmpRenderer = TmpLevel->GlobalActor->CreateRenderer("effect_015_tearpoofa.bmp", static_cast<int>(ORDER::Projectile));
		TmpRenderer->CreateAnimation("effect_015_tearpoofa.bmp", "effect_015_tearpoofa", 0, 15, 0.02f, false);
		TmpRenderer->ChangeAnimation("effect_015_tearpoofa");
		TmpRenderer->SetDeleteEndFrame_(true);
		TmpRenderer->SetPivot(GetPosition());
	}
	else
	{
		GameEngineRenderer* TmpRenderer = TmpLevel->GlobalActor->CreateRenderer("effect_003_bloodtear.bmp", static_cast<int>(ORDER::Projectile));
		TmpRenderer->CreateAnimation("effect_003_bloodtear.bmp", "effect_003_bloodtear", 0, 15, 0.02f, false);
		TmpRenderer->ChangeAnimation("effect_003_bloodtear");
		TmpRenderer->SetDeleteEndFrame_(true);
		TmpRenderer->SetPivot(GetPosition());
	}
	
	Death();
}

