#include "Clotty.h"
#include <GameEngineBase/GameEngineRandom.h>

Clotty::Clotty() 
	: State_(ClottyState::Default)
	, AnimTimer_(0.0f)
	, MoveDir_(float4::ZERO)
	, IsAttack_(false)
{
}

Clotty::~Clotty() 
{
}

void Clotty::Start()
{
	Collision_ = CreateCollision("Monster", {50, 50});
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_065_clotty_Right.bmp", "Idle_Right", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_065_clotty_Right.bmp", "Move_Right", 0, 8, 0.1f, true);
	Renderer_->CreateAnimation("monster_065_clotty_Right.bmp", "Attack_Right", 8, 10, 0.1f, false);
	Renderer_->CreateAnimation("monster_065_clotty_Left.bmp", "Idle_Left", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_065_clotty_Left.bmp", "Move_Left", 0, 8, 0.1f, true);
	Renderer_->CreateAnimation("monster_065_clotty_Left.bmp", "Attack_Left", 8, 10, 0.1f, false);
	Renderer_->ChangeAnimation("Idle_Right");

	
	SetHP(15);
	SetAttackDelay(3.0f);
	SetMoveSpeed(100.0f);
	ChangeState(ClottyState::Idle);
}

void Clotty::MonsterUpdate()
{
	StateUpdate();
	AttackTimer_ += GameEngineTime::GetDeltaTime();
	
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		ChangeState(ClottyState::Attack);
	}

	MonsterSetMoveToWalk(MoveDir_);
}

void Clotty::ChangeState(ClottyState _State)
{
	if (State_ == _State)
	{
		return;
	}

	State_ = _State;
	switch (State_)
	{
	case ClottyState::Idle:
		IdleStart();
		break;
	case ClottyState::Move:
		MoveStart();
		break;
	case ClottyState::Attack:
		AttackStart();
		break;
	default:
		break;
	}
}
void Clotty::StateUpdate()
{
	switch (State_)
	{
	case ClottyState::Idle:
		IdleUpdate();
		break;
	case ClottyState::Move:
		MoveUpdate();
		break;
	case ClottyState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}


void Clotty::IdleStart()
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

void Clotty::MoveStart()
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

void Clotty::AttackStart()
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

void Clotty::IdleUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	
	if (AnimTimer_ >= 0.25f)
	{
		AnimTimer_ = 0.0f;
		ChangeState(ClottyState::Move);
	}
}

void Clotty::MoveUpdate()
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

void Clotty::AttackUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.3f && IsAttack_ == false)
	{
		IsAttack_ = true;
		Shoot({400, 0}, ProjectileType::ENEMY_BASIC);
		Shoot({-400, 0}, ProjectileType::ENEMY_BASIC);
		Shoot({0, 400}, ProjectileType::ENEMY_BASIC);
		Shoot({0, -400}, ProjectileType::ENEMY_BASIC);
	}

	if (AnimTimer_ >= 0.6f)
	{
		ChangeState(ClottyState::Idle);
	}
}
