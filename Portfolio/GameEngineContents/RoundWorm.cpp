#include "RoundWorm.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "RoomActor.h"

RoundWorm::RoundWorm() 
	: State_(RoundWormState::Default)
	, AnimTimer_(0.0f)
	, IsAttack_(false)
{
}

RoundWorm::~RoundWorm() 
{
}

void RoundWorm::MoveRandomPos()
{
	float4 RandomPos = Room_->GetRandomPos();
	while (MonsterSetMoveToTeleport(RandomPos) == false)
	{
		RandomPos = Room_->GetRandomPos();
	}
}

void RoundWorm::Start()
{
	Collision_ = CreateCollision("Monster", {50, 50});
	Renderer_ = CreateRenderer("monster_244_roundworm.bmp", static_cast<int>(ORDER::PLAYER));
	Renderer_->SetIndex(0);
	ChangeState(RoundWormState::Idle);
	SetHP(10);
}

void RoundWorm::MonsterUpdate()
{


	StateUpdate();
}

void RoundWorm::ChangeState(RoundWormState _State)
{
	if (State_ == _State)
	{
		return;
	}

	State_ = _State;
	switch (State_)
	{
	case RoundWormState::Idle:
		IdleStart();
		break;
	case RoundWormState::Hide:
		HideStart();
		break;
	case RoundWormState::Show:
		ShowStart();
		break;
	case RoundWormState::Attack:
		AttackStart();
		break;
	default:
		break;
	}
}

void RoundWorm::StateUpdate()
{
	switch (State_)
	{
	case RoundWormState::Idle:
		IdleUpdate();
		break;
	case RoundWormState::Hide:
		HideUpdate();
		break;
	case RoundWormState::Show:
		ShowUpdate();
		break;
	case RoundWormState::Attack:
		AttackUpdate();
		break;
	default:
		break;
	}
}

void RoundWorm::IdleStart()
{
	AnimTimer_ = 0.0f;
}
void RoundWorm::HideStart()
{
	AnimTimer_ = 0.0f;
}
void RoundWorm::ShowStart()
{
	AnimTimer_ = 0.0f;
	Collision_->On();
	MoveRandomPos();
}
void RoundWorm::AttackStart()
{
	AnimTimer_ = 0.0f;
	IsAttack_ = false;
	Renderer_->SetIndex(2);
}

void RoundWorm::IdleUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 1.0f)
	{
		ChangeState(RoundWormState::Hide);
	}
}
void RoundWorm::HideUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (0.2f <= AnimTimer_ && AnimTimer_ < 0.4f)
	{
		Renderer_->SetIndex(4);
	}
	if (0.4f <= AnimTimer_ && AnimTimer_ < 0.6f)
	{
		Renderer_->SetIndex(5);
	}
	if (0.6f <= AnimTimer_ && AnimTimer_ < 0.8f)
	{
		Renderer_->SetIndex(6);
		Collision_->Off();
	}
	if (2.0f <= AnimTimer_)
	{
		ChangeState(RoundWormState::Show);
	}
}
void RoundWorm::ShowUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (0.2f <= AnimTimer_ && AnimTimer_ < 0.4f)
	{
		Renderer_->SetIndex(5);
	}
	if (0.4f <= AnimTimer_ && AnimTimer_ < 0.6f)
	{
		Renderer_->SetIndex(4);
	}
	if (0.6f <= AnimTimer_ && AnimTimer_ < 0.8f)
	{
		Renderer_->SetIndex(0);
	}
	if (1.0f <= AnimTimer_)
	{
		ChangeState(RoundWormState::Attack);
	}
}
void RoundWorm::AttackUpdate()
{
	if (IsAttack_ == false)
	{
		IsAttack_ = true;
		Shoot(AttackNormalDir() * 500.0f, ProjectileType::ENEMY_BASIC);
		ChangeState(RoundWormState::Idle);
	}
}
