#include "Host.h"

Host::Host() 
	: Type_(HostType::Normal)
	, State_(HostState::Idle)
	, AnimTimer_(0.0f)
{
}

Host::~Host() 
{
}

void Host::SetType(HostType _Type)
{
	Type_ = _Type;
	std::string TmpName;
	switch (Type_)
	{
	case HostType::Normal:
		TmpName = "monster_122_host.bmp";
		break;
	case HostType::Red:
		TmpName = "monster_127_redhost.bmp";
		break;
	default:
		break;
	}
	Renderer_ = CreateRenderer(TmpName, static_cast<int>(ORDER::PLAYER));
	Renderer_->SetIndex(0);
}

void Host::Start()
{
	Collision_ = CreateCollision("Monster", { 50, 50 }, {0, 50});

	SetAttackDelay(2.0f);
	SetHP(15);
}

void Host::MonsterUpdate()
{
	StateUpdate();
}

void Host::ChangeState(HostState _State)
{
	if (State_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case HostState::Idle:
		IdleStart();
		break;
	case HostState::Attack:
		AttackStart();
		break;
	default:
		break;
	}

	State_ = _State;
}

void Host::StateUpdate()
{
	switch (State_)
	{
	case HostState::Idle:
		IdleUpdate();
		break;
	case HostState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}

void Host::IdleStart()
{
	AnimTimer_ = 0.0f;
	Renderer_->SetIndex(0);

	if (Type_ == HostType::Normal)
	{
		IsInvincibility_ = true;
	}
}

void Host::AttackStart()
{
	AnimTimer_ = 0.0f;
	Renderer_->SetIndex(1);
	
	if (Type_ == HostType::Normal)
	{  
		IsInvincibility_ = false;
	}
}

void Host::IdleUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= AttackDelay_)
	{
		ChangeState(HostState::Attack);
	}
}

void Host::AttackUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.8f)
	{
		Shoot(AttackNormalDir() * 500.0f, ProjectileType::ENEMY_BASIC);
		ChangeState(HostState::Idle);
	}
}
