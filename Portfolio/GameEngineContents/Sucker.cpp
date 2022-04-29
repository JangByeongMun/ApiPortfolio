#include "Sucker.h"

Sucker::Sucker() 
{
}

Sucker::~Sucker() 
{
}

void Sucker::Start()
{
	Renderer_ = CreateRenderer(1);
	Renderer_->CreateAnimation("monster_078_sucker.bmp", "monster_078_sucker_Idle", 0, 1, 0.1f, true);
	Renderer_->ChangeAnimation("monster_078_sucker_Idle");
}

void Sucker::MonsterUpdate()
{
	MonsterSetMoveToFly(AttackNormalDir() * 300);
}

