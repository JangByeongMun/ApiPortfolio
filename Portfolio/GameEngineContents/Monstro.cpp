#include "Monstro.h"
#include <GameEngineBase/GameEngineRandom.h>

Monstro::Monstro()
	: AnimTimer_(0.0f)
	, IsAnim_(false)
	, State_(MonstroState::Idle)
{
}

Monstro::~Monstro() 
{
}

void Monstro::Start()
{
	Type_ = BossType::Monstro;
	SetHP(250.0f);
	SetMoveSpeed(250.0f);
	SetAttackDelay(1.0f);

	// ±×¸²ÀÚ
	GameEngineRenderer* Shadow = CreateRenderer("shadow.bmp", 0);
	Shadow->SetAlpha(70);
	Shadow->SetScale({ 220, 90 });
	Shadow->SetPivot({ 0, 90 });

	Collision_ = CreateCollision("Monster", { 200, 170 }, {0, 40});
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_0", 0, 0, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_1", 1, 1, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_2", 2, 2, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_3", 3, 3, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_4", 4, 4, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_5", 5, 5, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_6", 6, 6, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_7", 7, 7, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_8", 8, 8, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Left.bmp", "boss_004_monstro_Left_9", 9, 9, 0, false);

	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_0", 0, 0, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_1", 1, 1, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_2", 2, 2, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_3", 3, 3, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_4", 4, 4, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_5", 5, 5, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_6", 6, 6, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_7", 7, 7, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_8", 8, 8, 0, false);
	Renderer_->CreateAnimation("boss_004_monstro_Right.bmp", "boss_004_monstro_Right_9", 9, 9, 0, false);
	Renderer_->ChangeAnimation("boss_004_monstro_Left_2");

	RendererName_Left = "boss_004_monstro_Left";
	RendererName_Right = "boss_004_monstro_Right";
}

void Monstro::MonsterUpdate()
{
	StateUpdate();
}

void Monstro::MonsterDeath()
{
	ChangeState(MonstroState::Dead);
}

void Monstro::IdleStart()
{
	ChangeMonstroAnimation("_2");
}

void Monstro::LargeJumpStart()
{
	ChangeMonstroAnimation("_5");
	AnimTimer_ = 0.0f;
	IsAnim_ = true;
}

void Monstro::SmallJumpStart()
{
	ChangeMonstroAnimation("_5");
	AnimTimer_ = 0.0f;
}

void Monstro::AttackStart()
{
	ChangeMonstroAnimation("_1");
	AnimTimer_ = 0.0f;
	IsAnim_ = true;
}

void Monstro::DeadStart()
{
	ChangeMonstroAnimation("_8");
	AnimTimer_ = 0.0f;
	IsAnim_ = true;
}

void Monstro::IdleUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 3);
		ChangeState(static_cast<MonstroState>(RandomInt));
	}
}

void Monstro::LargeJumpUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	
	if (AnimTimer_ >= 1.7f)
	{
		ChangeState(MonstroState::Idle);
		return;
	}
	else if (AnimTimer_ >= 1.5f)
	{
		ChangeMonstroAnimation("_5");
		Collision_->On();
		if (true == IsAnim_)
		{
			IsAnim_ = false;
			for (int i = 0; i < 7; i++)
			{
				float4 RandomPos = float4(GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f), GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f));
				RandomPos = RandomPos * 200.0f;
				Shoot(RandomPos, ProjectileType::ENEMY_BASIC);
			}
		}
		return;
	}
	else if (AnimTimer_ >= 1.3f)
	{
		ChangeMonstroAnimation("_4");
		float4 LerpFloat4 = float4::Lerp(float4(0, -700), float4(0, 0), (AnimTimer_ - 1.3f) * 5.0f);
		Renderer_->SetPivot(LerpFloat4);
		return;
	}
	else if (AnimTimer_ >= 0.3f)
	{
		ChangeMonstroAnimation("_6");
		float4 LerpFloat4 = float4::Lerp(float4(0, 0), float4(0, -700), (AnimTimer_ - 0.3f) * 4.0f);
		Renderer_->SetPivot(LerpFloat4);
		Collision_->Off();
		MonsterSetMove(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
		return;
	}
}

void Monstro::SmallJumpUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ >= 1.5f)
	{
		ChangeState(MonstroState::Idle);
		return;
	}
	else if (AnimTimer_ >= 1.3f)
	{
		ChangeMonstroAnimation("_8");
		return;
	}
	else if (AnimTimer_ >= 1.2f)
	{
		ChangeMonstroAnimation("_5");
		return;
	}
	else if (AnimTimer_ >= 1.0f)
	{
		ChangeMonstroAnimation("_4");
		float4 LerpFloat4 = float4::Lerp(float4(0, -200), float4(0, 0), (AnimTimer_ - 1.0f) * 5.0f);
		Renderer_->SetPivot(LerpFloat4);
		MonsterSetMove(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
		return;
	}
	else if (AnimTimer_ >= 0.5f)
	{
		ChangeMonstroAnimation("_7");
		MonsterSetMove(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
		return;
	}
	else if (AnimTimer_ >= 0.3f)
	{
		ChangeMonstroAnimation("_6");
		float4 LerpFloat4 = float4::Lerp(float4(0, 0), float4(0, -200), (AnimTimer_ - 0.3f) * 4.0f);
		Renderer_->SetPivot(LerpFloat4);
		MonsterSetMove(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
		return;
	}
}

void Monstro::AttackUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 1.3f)
	{
		ChangeState(MonstroState::Idle);
		return;
	}
	else if (AnimTimer_ >= 1.1f)
	{
		ChangeMonstroAnimation("_8");
		return;
	}
	else if (AnimTimer_ >= 0.5f)
	{
		ChangeMonstroAnimation("_3");
		if (true == IsAnim_)
		{
			IsAnim_ = false;
			for (int i = 0; i < 7; i++)
			{
				float4 RandomPos = AttackNormalDir() * 350.0f;
				RandomPos += float4(GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f), GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f)) * 60;
				Shoot(RandomPos, ProjectileType::ENEMY_BASIC);
			}
		}
		return;
	}
}

void Monstro::DeadUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 1.4f)
	{
		Death();
		return;
	}
	else if (AnimTimer_ >= 0.9f)
	{
		if (true == IsAnim_)
		{
			IsAnim_ = false;
			GameEngineRenderer* TmpRenderer = CreateRenderer("effect_002_bloodpoof.bmp", static_cast<int>(ORDER::FRONTUI));
			TmpRenderer->CreateAnimation("effect_002_bloodpoof.bmp", "effect_002_bloodpoof", 0, 15, 0.04f, false);
			TmpRenderer->ChangeAnimation("effect_002_bloodpoof");
			TmpRenderer->SetPivot({ GameEngineRandom::MainRandom->RandomFloat(-85, 85), GameEngineRandom::MainRandom->RandomFloat(-85, 85) });
		}
		return;
	}
	else if (AnimTimer_ >= 0.6f)
	{
		if (false == IsAnim_)
		{
			IsAnim_ = true;
			GameEngineRenderer* TmpRenderer = CreateRenderer("effect_002_bloodpoof.bmp", static_cast<int>(ORDER::FRONTUI));
			TmpRenderer->CreateAnimation("effect_002_bloodpoof.bmp", "effect_002_bloodpoof", 0, 15, 0.04f, false);
			TmpRenderer->ChangeAnimation("effect_002_bloodpoof");
			TmpRenderer->SetPivot({ GameEngineRandom::MainRandom->RandomFloat(-85, 85), GameEngineRandom::MainRandom->RandomFloat(-85, 85) });
		}
		return;
	}
	else if (AnimTimer_ >= 0.3f)
	{
		if (true == IsAnim_)
		{
			IsAnim_ = false;
			GameEngineRenderer* TmpRenderer = CreateRenderer("effect_002_bloodpoof.bmp", static_cast<int>(ORDER::FRONTUI));
			TmpRenderer->CreateAnimation("effect_002_bloodpoof.bmp", "effect_002_bloodpoof", 0, 15, 0.04f, false);
			TmpRenderer->ChangeAnimation("effect_002_bloodpoof");
			TmpRenderer->SetPivot({ GameEngineRandom::MainRandom->RandomFloat(-85, 85), GameEngineRandom::MainRandom->RandomFloat(-85, 85) });
		}

		return;
	}
}

void Monstro::ChangeState(MonstroState _State)
{
	if (State_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case MonstroState::Idle:
		IdleStart();
		break;
	case MonstroState::LargeJump:
		LargeJumpStart();
		break;
	case MonstroState::SmallJump:
		SmallJumpStart();
		break;
	case MonstroState::Attack:
		AttackStart();
		break;
	case MonstroState::Dead:
		DeadStart();
		break;
	default:
		break;
	}
	
	State_ = _State;
}

void Monstro::StateUpdate()
{
	switch (State_)
	{
	case MonstroState::Idle:
		IdleUpdate();
		break;
	case MonstroState::LargeJump:
		LargeJumpUpdate();
		break;
	case MonstroState::SmallJump:
		SmallJumpUpdate();
		break;
	case MonstroState::Attack:
		AttackUpdate();
		break;
	case MonstroState::Dead:
		DeadUpdate();
		break;
	default:
		break;
	}
}