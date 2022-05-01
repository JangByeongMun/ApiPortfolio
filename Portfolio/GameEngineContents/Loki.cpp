#include "Loki.h"
#include "RoomActor.h"
#include "BoomFly.h"

Loki::Loki() 
	: State_(LokiState::Idle)
	, AnimTimer_(0.0f)
	, IsAnim_(false)
	, ShadowRenderer_(nullptr)
{
}

Loki::~Loki() 
{
}

void Loki::MoveRandomPos()
{
	float4 RandomPos = Room_->GetRandomPos();
	while (MonsterSetMoveToTeleport(RandomPos) == false)
	{
		RandomPos = Room_->GetRandomPos();
	}
}

void Loki::Start()
{
	Type_ = BossType::Loki;
	SetHP(350.0f);
	SetMoveSpeed(100.0f);
	SetAttackDelay(0.8f);

	// ±×¸²ÀÚ
	ShadowRenderer_ = CreateRenderer("shadow.bmp", 0);
	ShadowRenderer_->SetAlpha(70);
	ShadowRenderer_->SetScale({ 100, 40 });
	ShadowRenderer_->SetPivot({ 0, 90 });

	Collision_ = CreateCollision("Monster", { 80, 80 });
	Renderer_ = CreateRenderer("boss_048_loki.bmp", static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("boss_048_loki.bmp", "Idle", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "Jump_1", 7, 7, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "Jump_2", 6, 6, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "ShootOnce", 15, 17, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "ShootTriple1_1", 4, 5, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "ShootTriple1_2", 2, 2, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "ShootTriple2_1", 17, 17, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "ShootTriple2_2", 10, 10, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "ShootTriple3_1", 9, 9, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "Summon", 11, 14, 0.1f, false);
	Renderer_->CreateAnimation("boss_048_loki.bmp", "Dead", 3, 5, 0.1f, false);
	Renderer_->ChangeAnimation("Idle");
}

void Loki::MonsterUpdate()
{
	StateUpdate();
}

void Loki::MonsterDeath()
{
	ChangeState(LokiState::Dead);
}

void Loki::ChangeState(LokiState _State)
{
	if (State_ == _State)
	{
		return;
	}
	
	State_ = _State;
	switch (_State)
	{
	case LokiState::Idle:
		IdleStart();
		break;
	case LokiState::Jump:
		JumpStart();
		break;
	case LokiState::ShootOnce:
		ShootOnceStart();
		break;
	case LokiState::ShootTriple:
		ShootTripleStart();
		break;
	case LokiState::Summon:
		SummonStart();
		break;
	case LokiState::Dead:
		DeadStart();
		break;
	default:
		break;
	}
}

void Loki::StateUpdate()
{
	switch (State_)
	{
	case LokiState::Idle:
		IdleUpdate();
		break;
	case LokiState::Jump:
		JumpUpdate();
		break;
	case LokiState::ShootOnce:
		ShootOnceUpdate();
		break;
	case LokiState::ShootTriple:
		ShootTripleUpdate();
		break;
	case LokiState::Summon:
		SummonUpdate();
		break;
	case LokiState::Dead:
		DeadUpdate();
		break;
	default:
		break;
	}
}

void Loki::IdleStart()
{
	AttackTimer_ = 0.0f;
	Renderer_->ChangeAnimation("Idle");
}
void Loki::JumpStart()
{
	AnimTimer_ = 0.0f;
	IsAnim_ = false;
	Renderer_->ChangeAnimation("Jump_1");
}
void Loki::ShootOnceStart()
{
	AnimTimer_ = 0.0f;
	IsAnim_ = false;
	Renderer_->ChangeAnimation("ShootOnce");
}
void Loki::ShootTripleStart()
{
	AnimTimer_ = 0.0f;
	IsAnim_ = false;
	Renderer_->ChangeAnimation("ShootTriple1_1");
}
void Loki::SummonStart()
{
	AnimTimer_ = 0.0f;
	IsAnim_ = false;
	Renderer_->ChangeAnimation("Summon");
}
void Loki::DeadStart()
{
	AnimTimer_ = 0.0f;
	IsAnim_ = false;
	Renderer_->ChangeAnimation("Dead");

	GameEngineRenderer* TmpRenderer = CreateRenderer("effect_002_bloodpoof.bmp", static_cast<int>(ORDER::FRONTUI));
	TmpRenderer->CreateAnimation("effect_002_bloodpoof.bmp", "effect_002_bloodpoof", 0, 15, 0.04f, false);
	TmpRenderer->ChangeAnimation("effect_002_bloodpoof");
	TmpRenderer->SetPivot({ GameEngineRandom::MainRandom->RandomFloat(-40, 40), GameEngineRandom::MainRandom->RandomFloat(-40, 40) });
}


void Loki::IdleUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 4);
		ChangeState(static_cast<LokiState>(RandomInt));
	}

	MonsterSetMoveToWalk(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
}

void Loki::JumpUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (1.0f <= AnimTimer_ && AnimTimer_ < 2.0f)
	{
		Collision_->Off();
		ShadowRenderer_->Off();
		Renderer_->ChangeAnimation("Jump_2");

		float4 LerpPos = float4::Lerp({ 0, 0 }, {0, -700}, (AnimTimer_ - 1.0f) * 2.0f);
		Renderer_->SetPivot(LerpPos);
	}
	if (2.0f <= AnimTimer_ && AnimTimer_ < 3.0f)
	{
		Collision_->On();
		ShadowRenderer_->On();

		float4 LerpPos = float4::Lerp({ 0, -700 }, { 0, 0 }, (AnimTimer_ - 2.0f) * 2.0f);
		Renderer_->SetPivot(LerpPos);

		if (IsAnim_ == false)
		{
			IsAnim_ = true;
			MoveRandomPos();
		}
	}
	if (2.5f <= AnimTimer_)
	{
		Renderer_->ChangeAnimation("Jump_1");
	}
	if (3.0f <= AnimTimer_)
	{
		ChangeState(LokiState::Idle);
	}
}

void Loki::ShootOnceUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (0.2f <= AnimTimer_ && IsAnim_ == false)
	{
		IsAnim_ = true;

		Shoot({ 400, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -400, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 0, 400 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 0, -400 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 300, 300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 300, -300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, 300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, -300 }, ProjectileType::ENEMY_BASIC);
	}

	if (0.7f <= AnimTimer_)
	{
		ChangeState(LokiState::Idle);
	}
}

void Loki::ShootTripleUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (0.2f <= AnimTimer_ && AnimTimer_ < 0.3f)
	{
		if (IsAnim_ == false)
		{
			IsAnim_ = true;
			Renderer_->ChangeAnimation("ShootTriple1_2");

			Shoot({ 400, 0 }, ProjectileType::ENEMY_BASIC);
			Shoot({ -400, 0 }, ProjectileType::ENEMY_BASIC);
			Shoot({ 0, 400 }, ProjectileType::ENEMY_BASIC);
			Shoot({ 0, -400 }, ProjectileType::ENEMY_BASIC);
		}
	}
	if (0.8f <= AnimTimer_ && AnimTimer_ < 0.9f)
	{
		Renderer_->ChangeAnimation("ShootTriple2_1");
	}
	if (0.9f <= AnimTimer_ && AnimTimer_ < 1.0f)
	{
		if (IsAnim_ == true)
		{
			IsAnim_ = false;
			Renderer_->ChangeAnimation("ShootTriple2_2");

			Shoot({ 300, 300 }, ProjectileType::ENEMY_BASIC);
			Shoot({ 300, -300 }, ProjectileType::ENEMY_BASIC);
			Shoot({ -300, 300 }, ProjectileType::ENEMY_BASIC);
			Shoot({ -300, -300 }, ProjectileType::ENEMY_BASIC);
		}
	}
	if (1.6f <= AnimTimer_ && AnimTimer_ < 1.7f)
	{
		if (IsAnim_ == false)
		{
			IsAnim_ = true;
			Renderer_->ChangeAnimation("ShootTriple3_1");

			Shoot({ 400, 0 }, ProjectileType::ENEMY_BASIC);
			Shoot({ -400, 0 }, ProjectileType::ENEMY_BASIC);
			Shoot({ 0, 400 }, ProjectileType::ENEMY_BASIC);
			Shoot({ 0, -400 }, ProjectileType::ENEMY_BASIC);
		}
	}

	if (2.5f <= AnimTimer_)
	{
		ChangeState(LokiState::Idle);
	}
}

void Loki::SummonUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (0.5f <= AnimTimer_ && IsAnim_ == false)
	{
		IsAnim_ = true;
		BoomFly* TmpMonster = GetLevel()->CreateActor<BoomFly>();
		TmpMonster->SetPosition(GetPosition());
		TmpMonster->SetRoom(*Room_);
		TmpMonster->Setting(BoomFlyType::Normal);
	}

	if (1.0f <= AnimTimer_)
	{
		ChangeState(LokiState::Idle);
	}
}

void Loki::DeadUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (0.5f <= AnimTimer_)
	{
		Off();
	}
}

