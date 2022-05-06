#include "Spit.h"

Spit::Spit() 
{
}

Spit::~Spit() 
{
}

void Spit::Start()
{
	Collision_ = CreateCollision("Monster", { 50, 50 });
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_079_spit_Left.bmp", "Idle_Left", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("monster_079_spit_Right.bmp", "Idle_Right", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("Idle_Left");

	SetHP(10);
	SetMoveSpeed(100.0f);
}

void Spit::MonsterUpdate()
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

void Spit::MonsterDeath()
{
	for (int i = 0; i < 2; i++)
	{
		float4 RandomPos = float4(GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f), GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f)) * 200;
		Shoot(RandomPos, ProjectileType::ENEMY_IPECAC);
	}
}
