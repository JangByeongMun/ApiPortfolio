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
	Renderer_->CreateAnimation("monster_078_sucker_Left.bmp", "Idle_Left", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("monster_078_sucker_Right.bmp", "Idle_Right", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("Idle_Left");

	SetHP(10);
	SetMoveSpeed(100.0f);
}

void Sucker::MonsterUpdate()
{
	float4 MoveDir_ = AttackNormalDir() * GameEngineTime::GetDeltaTime() * MoveSpeed_;
	MonsterSetMoveToFly(MoveDir_);

	if (IsLeft_)
	{
		Renderer_->ChangeAnimation("Idle_Left");
	}
	else
	{
		Renderer_->ChangeAnimation("Idle_Right");
	}
}

void Sucker::MonsterDeath()
{
	Shoot({400, 0}, ProjectileType::ENEMY_BASIC);
	Shoot({-400, 0}, ProjectileType::ENEMY_BASIC);
	Shoot({0, 400}, ProjectileType::ENEMY_BASIC);
	Shoot({0, -400}, ProjectileType::ENEMY_BASIC);
}