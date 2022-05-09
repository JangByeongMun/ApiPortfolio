#include "Pooter.h"
#include "RoomActor.h"
#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

Pooter::Pooter()
	: IsAttackAnim(false)
{
}

Pooter::~Pooter()
{
}

void Pooter::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_001_pooter_Right.bmp", "monster_001_pooter_Idle_Right", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("monster_001_pooter_Right.bmp", "monster_001_pooter_Attack_Right", 2, 15, 0.05f, false);
	Renderer_->CreateAnimation("monster_001_pooter_Left.bmp", "monster_001_pooter_Idle_Left", 0, 1, 0.1f, true);
	Renderer_->CreateAnimation("monster_001_pooter_Left.bmp", "monster_001_pooter_Attack_Left", 2, 15, 0.05f, false);
	Renderer_->ChangeAnimation("monster_001_pooter_Idle_Left");

	Collision_ = CreateCollision("Monster", { 80, 80 });

	SetHP(8.0f);
	SetMoveSpeed(10.0f);
}

void Pooter::MonsterUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();

	// 공격애니메이션 발동
	if (AttackTimer_ >= AttackDelay_ - 0.5f && false == IsAttackAnim)
	{
		IsAttackAnim = true;
		if (IsLeft_)
		{
			Renderer_->ChangeAnimation("monster_001_pooter_Attack_Left");
		}
		else
		{
			Renderer_->ChangeAnimation("monster_001_pooter_Attack_Right");
		}
	}

	// 공격실행
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		Attack();
	}

	// 공격애니메이션 끝났을때
	if (true == IsAttackAnim && true == Renderer_->IsEndAnimation())
	{
		IsAttackAnim = false;
	}

	// 공격중이 아닐때
	if (false == IsAttackAnim)
	{
		if (IsLeft_)
		{
			Renderer_->ChangeAnimation("monster_001_pooter_Idle_Left");
		}
		else
		{
			Renderer_->ChangeAnimation("monster_001_pooter_Idle_Right");
		}

		MonsterSetMoveToFly(AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime());
	}
}

void Pooter::Attack()
{
	Shoot(AttackNormalDir() * 500.0f, ProjectileType::ENEMY_BASIC, { 0, 10 }, 1.0f);
}

void Pooter::MonsterDeath()
{
	std::string TmpName = "DeathBurstSmall";
	TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(0, 2)) + ".wav";
	GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 0.1f * Option_SFX);
}
