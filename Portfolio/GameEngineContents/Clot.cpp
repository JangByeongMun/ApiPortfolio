#include "Clot.h"

Clot::Clot() 
	: State_(ClotState::Default)
	, AnimTimer_(0.0f)
	, MoveDir_(float4::ZERO)
	, IsAttack_(false)
{
}

Clot::~Clot() 
{
}

void Clot::Start()
{
	Collision_ = CreateCollision("Monster", { 50, 50 });
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_071_clot_Right.bmp", "Idle_Right", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_071_clot_Right.bmp", "Move_Right", 0, 8, 0.1f, true);
	Renderer_->CreateAnimation("monster_071_clot_Right.bmp", "Attack_Right", 8, 10, 0.1f, false);
	Renderer_->CreateAnimation("monster_071_clot_Left.bmp", "Idle_Left", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_071_clot_Left.bmp", "Move_Left", 0, 8, 0.1f, true);
	Renderer_->CreateAnimation("monster_071_clot_Left.bmp", "Attack_Left", 8, 10, 0.1f, false);
	Renderer_->ChangeAnimation("Idle_Right");


	SetHP(15);
	SetAttackDelay(3.0f);
	SetMoveSpeed(100.0f);
	ChangeState(ClotState::Idle);
}

void Clot::MonsterUpdate()
{
	StateUpdate();
	AttackTimer_ += GameEngineTime::GetDeltaTime();

	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		ChangeState(ClotState::Attack);
	}

	MonsterSetMoveToWalk(MoveDir_);
}

void Clot::ChangeState(ClotState _State)
{
	if (State_ == _State)
	{
		return;
	}

	State_ = _State;
	switch (State_)
	{
	case ClotState::Idle:
		IdleStart();
		break;
	case ClotState::Move:
		MoveStart();
		break;
	case ClotState::Attack:
		AttackStart();
		break;
	default:
		break;
	}
}

void Clot::StateUpdate()
{
	switch (State_)
	{
	case ClotState::Idle:
		IdleUpdate();
		break;
	case ClotState::Move:
		MoveUpdate();
		break;
	case ClotState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}

void Clot::IdleStart()
{
	AnimTimer_ = 0.0f;
	MoveDir_ = float4::ZERO;

	if (IsLeft_)
	{
		Renderer_->ChangeAnimation("Idle_Left");
	}
	else
	{
		Renderer_->ChangeAnimation("Idle_Right");
	}
}

void Clot::MoveStart()
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

void Clot::AttackStart()
{
	AnimTimer_ = 0.0f;
	MoveDir_ = float4::ZERO;
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

void Clot::IdleUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ >= 0.25f)
	{
		AnimTimer_ = 0.0f;
		ChangeState(ClotState::Move);
	}
}

void Clot::MoveUpdate()
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

void Clot::AttackUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.3f && IsAttack_ == false)
	{
		IsAttack_ = true;
		Shoot({ 300, 300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 300, -300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, 300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, -300 }, ProjectileType::ENEMY_BASIC);
	}

	if (AnimTimer_ >= 0.6f)
	{
		ChangeState(ClotState::Idle);
	}
}
