#include "Iblob.h"
#include <GameEngineBase/GameEngineRandom.h>

Iblob::Iblob() 
	: State_(IblobState::Default)
	, AnimTimer_(0.0f)
	, MoveDir_(float4::ZERO)
	, IsAttack_(false)
{
}

Iblob::~Iblob() 
{
}

void Iblob::Start()
{
	Collision_ = CreateCollision("Monster", { 50, 50 });
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_075_lblob_Right.bmp", "Idle_Right", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_075_lblob_Right.bmp", "Move_Right", 0, 8, 0.1f, true);
	Renderer_->CreateAnimation("monster_075_lblob_Right.bmp", "Attack_Right", 8, 10, 0.1f, false);
	Renderer_->CreateAnimation("monster_075_lblob_Left.bmp", "Idle_Left", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_075_lblob_Left.bmp", "Move_Left", 0, 8, 0.1f, true);
	Renderer_->CreateAnimation("monster_075_lblob_Left.bmp", "Attack_Left", 8, 10, 0.1f, false);
	Renderer_->ChangeAnimation("Idle_Right");


	SetHP(15);
	SetAttackDelay(3.0f);
	SetMoveSpeed(100.0f);
	ChangeState(IblobState::Idle);
}

void Iblob::MonsterUpdate()
{
	StateUpdate();
	AttackTimer_ += GameEngineTime::GetDeltaTime();

	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		ChangeState(IblobState::Attack);
	}

	MonsterSetMoveToWalk(MoveDir_);
}

void Iblob::ChangeState(IblobState _State)
{
	if (State_ == _State)
	{
		return;
	}

	State_ = _State;
	switch (State_)
	{
	case IblobState::Idle:
		IdleStart();
		break;
	case IblobState::Move:
		MoveStart();
		break;
	case IblobState::Attack:
		AttackStart();
		break;
	default:
		break;
	}
}

void Iblob::StateUpdate()
{
	switch (State_)
	{
	case IblobState::Idle:
		IdleUpdate();
		break;
	case IblobState::Move:
		MoveUpdate();
		break;
	case IblobState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}

void Iblob::IdleStart()
{
	AnimTimer_ = 0.0f;
	if (IsLeft_)
	{
		Renderer_->ChangeAnimation("Idle_Left");
	}
	else
	{
		Renderer_->ChangeAnimation("Idle_Right");
	}
}

void Iblob::MoveStart()
{
	AnimTimer_ = 0.0f;
	if (MoveDir_.x <= 0)
	{
		Renderer_->ChangeAnimation("Move_Left");
	}
	else
	{
		Renderer_->ChangeAnimation("Move_Right");
	}
}

void Iblob::AttackStart()
{
	AnimTimer_ = 0.0f;
	IsAttack_ = false;
	if (IsLeft_)
	{
		Renderer_->ChangeAnimation("Attack_Left");
	}
	else
	{
		Renderer_->ChangeAnimation("Attack_Right");
	}
}

void Iblob::IdleUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ >= 0.25f)
	{
		ChangeState(IblobState::Move);
	}
}

void Iblob::MoveUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ >= 0.8f)
	{
		AnimTimer_ = 0.0f;
		MoveDir_ = float4(GameEngineRandom::MainRandom->RandomFloat(-2, 2), GameEngineRandom::MainRandom->RandomFloat(-2, 2));
		MoveDir_.Normal2D();
		MoveDir_ *= GameEngineTime::GetDeltaTime() * MoveSpeed_;

		if (MoveDir_.x <= 0)
		{
			Renderer_->ChangeAnimation("Move_Left");
		}
		else
		{
			Renderer_->ChangeAnimation("Move_Right");
		}
	}
}

void Iblob::AttackUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.3f && IsAttack_ == false)
	{
		IsAttack_ = true;
		Shoot({ 300, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 200, 200 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 200, -200 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -200, 200 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -200, -200 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 0, 300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 0, -300 }, ProjectileType::ENEMY_BASIC);
	}

	if (AnimTimer_ >= 0.6f)
	{
		ChangeState(IblobState::Idle);
	}
}

