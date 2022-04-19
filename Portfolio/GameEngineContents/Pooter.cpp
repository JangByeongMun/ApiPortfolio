#include "Pooter.h"
#include "RoomActor.h"
#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineTime.h>

Pooter::Pooter() 
{
}

Pooter::~Pooter() 
{
}

void Pooter::Start()
{
	Renderer_ = CreateRenderer(1);
	Renderer_->CreateAnimation("monster_001_pooter.bmp", "monster_001_pooter_Idle", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("monster_001_pooter.bmp", "monster_001_pooter_Attack", 2, 15, 0.05f, false);
	Renderer_->ChangeAnimation("monster_001_pooter_Idle");
}

void Pooter::MonsterUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();

	if (AttackTimer_ >= AttackDelay_ - 0.5f)
	{
		Renderer_->ChangeAnimation("monster_001_pooter_Attack");
	}
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		Attack();
	}

	if (true == Renderer_->IsEndAnimation())
	{
		Renderer_->ChangeAnimation("monster_001_pooter_Idle");
	}

	MonsterSetMove(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
}

void Pooter::Attack()
{
	Shoot(AttackNormalDir() * 500.0f, ProjectileType::ENEMY_BASIC);
}
