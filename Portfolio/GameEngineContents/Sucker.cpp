#include "Sucker.h"

Sucker::Sucker() 
{
}

Sucker::~Sucker() 
{
}

void Sucker::Start()
{
	Collision_ = CreateCollision("Monster", {50, 50});
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_078_sucker.bmp", "monster_078_sucker_Idle", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("monster_078_sucker_Idle");
}

void Sucker::MonsterUpdate()
{
	float4 MoveDir_ = AttackNormalDir() * GameEngineTime::GetDeltaTime() * MoveSpeed_;
	MonsterSetMoveToFly(MoveDir_);
}

void Sucker::MonsterDeath()
{
	Shoot({300, 0}, ProjectileType::ENEMY_BASIC);
	Shoot({-300, 0}, ProjectileType::ENEMY_BASIC);
	Shoot({0, 300}, ProjectileType::ENEMY_BASIC);
	Shoot({0, -300}, ProjectileType::ENEMY_BASIC);
}