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

	// 플레이어의 눈물이면
	if (static_cast<int>(Type_) < static_cast<int>(ProjectileType::ENEMY_BASIC))
	{
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
				}
			}
		}
	}

	// 적의 눈물이면
	if (static_cast<int>(Type_) >= static_cast<int>(ProjectileType::ENEMY_BASIC))
	{

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
	GameEngineRenderer* TmpRenderer = TmpLevel->GlobalActor->CreateRenderer("effect_015_tearpoofa.bmp");
	TmpRenderer->CreateAnimation("effect_015_tearpoofa.bmp", "effect_015_tearpoofa", 0, 15, 0.02f, false);
	TmpRenderer->ChangeAnimation("effect_015_tearpoofa");
	TmpRenderer->SetDeleteEndFrame_(true);
	TmpRenderer->SetPivot(GetPosition());
	Death();
}

