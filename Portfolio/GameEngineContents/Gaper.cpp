#include "Gaper.h"

Gaper::Gaper() 
{
}

Gaper::~Gaper() 
{
}

void Gaper::Start()
{
	Renderer_ = CreateRenderer(1);
	Renderer_->CreateAnimation("monster_017_gaper.bmp", "monster_017_gaper_Idle", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("monster_017_gaper.bmp", "monster_017_gaper_Attack", 2, 15, 0.05f, false);
	Renderer_->ChangeAnimation("monster_017_gaper_Idle");
}

void Gaper::MonsterUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();

	if (AttackTimer_ >= AttackDelay_ - 0.5f)
	{
		Renderer_->ChangeAnimation("monster_017_gaper_Attack");
	}
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		Attack();
	}

	if (true == Renderer_->IsEndAnimation())
	{
		Renderer_->ChangeAnimation("monster_017_gaper_Idle");
	}
}

void Gaper::Attack()
{
	Shoot(AttackNormalDir() * 500.0f, ProjectileType::ENEMY_BASIC);
}

