#include "Fly.h"

Fly::Fly() 
	: Type_(FlyType::Normal)
	, DeadRenderer_(nullptr)
{
}

Fly::~Fly() 
{
}

void Fly::SetType(FlyType _Type)
{
	Type_ = _Type;
	Collision_ = CreateCollision("Monster", {30, 30});
	switch (Type_)
	{
	case FlyType::Normal:
		SetAttack(false);
		SetHP(3);
		Renderer_->ChangeAnimation("Normal");
		SetMoveSpeed(10.0f);
		break;
	case FlyType::Red:
		SetAttack(true);
		SetHP(5);
		Renderer_->ChangeAnimation("Red");
		SetMoveSpeed(100.0f);
		break;
	default:
		break;
	}
}

void Fly::Start()
{
	Renderer_ = CreateRenderer("monster_010_fly.bmp", static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_010_fly.bmp", "Normal", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("monster_010_fly.bmp", "Red", 4, 7, 0.1f, true);
	Renderer_->ChangeAnimation("Normal");

	DeadRenderer_ = CreateRenderer("monster_010_eternalfly_Dead.bmp", static_cast<int>(ORDER::PLAYER));
	DeadRenderer_->CreateAnimation("monster_010_eternalfly_Dead.bmp", "Dead", 0, 11, 0.1f, false);
	DeadRenderer_->CreateAnimation("None.bmp", "None", 0, 0, 0.1f, false);
	DeadRenderer_->ChangeAnimation("None");
}

void Fly::MonsterUpdate()
{
	MonsterSetMoveToFly(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
}

void Fly::MonsterDeath()
{
	Renderer_->Off();
	DeadRenderer_->ChangeAnimation("Dead");
}