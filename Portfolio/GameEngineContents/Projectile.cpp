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
#include "BoomEffect.h"

Projectile::Projectile() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
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

	if (ProjectileType::ENEMY_IPECAC == Type_)
	{
		if (Lifetime_ * 0.5f > CurrentTimer_)
		{
			float4 LerpPos = float4::Lerp({ 0, 0 }, {0, -120}, CurrentTimer_ / (Lifetime_ * 0.5f));
			Renderer_->SetPivot(LerpPos);
		}
		else
		{
			float4 LerpPos = float4::Lerp({ 0, -120 }, { 0, 0 }, (CurrentTimer_ - (Lifetime_ * 0.5f)) / (Lifetime_ * 0.5f));
			Renderer_->SetPivot(LerpPos);
		}
	}
	else
	{
		if (Lifetime_ - CurrentTimer_ <= 0.3f)
		{
			Vec_ += {0, 600 * GameEngineTime::GetDeltaTime()};
		}
	}

	// ������ �ð��� ������ ����
	if (Lifetime_ - CurrentTimer_ <= 0.0f)
	{
		DestroyProjectile();
	}

	// ���� �浹������
	if (true == Collision_->CollisionCheckRect("Stone"))
	{
		DestroyProjectile();
	}

	if (true == Collision_->CollisionCheckRect("NoDamageMonster"))
	{
		DestroyProjectile();
	}

	// �Ұ� �浹������
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

	// �˰� �浹������
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

	// �÷��̾��� �����̸�
	if (true == IsPlayerProjectile())
	{
		// ���Ϳ� �浹������
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

	// ���� �����̸�
	if (false == IsPlayerProjectile())
	{
		std::vector<GameEngineCollision*> CollisionResult;
		if (true == Collision_->CollisionCheckRect("Player"))
		{
			Player::MainPlayer->GetPlayerHP()->MinusHearts(true);
			DestroyProjectile();
		}
	}
	
	// ���� ���Ѿ���� �Ѿ�����ϸ� ����
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

	if (Type_ == ProjectileType::ENEMY_IPECAC) // ������
	{
		TmpLevel->CreateActor<BoomEffect>()->Setting(GetPosition());
	}
	else
	{
		if (true == IsPlayerProjectile())
		{
			GameEngineRenderer* TmpRenderer = TmpLevel->GlobalActor->CreateRenderer("effect_015_tearpoofa.bmp", static_cast<int>(ORDER::PLAYER));
			TmpRenderer->CreateAnimation("effect_015_tearpoofa.bmp", "effect_015_tearpoofa", 0, 15, 0.02f, false);
			TmpRenderer->ChangeAnimation("effect_015_tearpoofa");
			TmpRenderer->SetDeleteEndFrame_(true);
			TmpRenderer->SetPivot(GetPosition());
		}
		else
		{
			GameEngineRenderer* TmpRenderer = TmpLevel->GlobalActor->CreateRenderer("effect_003_bloodtear.bmp", static_cast<int>(ORDER::PLAYER));
			TmpRenderer->CreateAnimation("effect_003_bloodtear.bmp", "effect_003_bloodtear", 0, 15, 0.02f, false);
			TmpRenderer->ChangeAnimation("effect_003_bloodtear");
			TmpRenderer->SetDeleteEndFrame_(true);
			TmpRenderer->SetPivot(GetPosition());
		}

		GameEngineSound::SoundPlayOneShotWithVolume("tear block.wav", 0, 0.1f * Option_SFX);
	}
	
	Death();
}

