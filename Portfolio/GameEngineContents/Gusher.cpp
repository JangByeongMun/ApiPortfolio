#include "Gusher.h"
#include <GameEngineBase/GameEngineRandom.h>

Gusher::Gusher()
	: MoveDir_({})
{
}

Gusher::~Gusher() 
{
}

void Gusher::Start()
{
	Collision_ = CreateCollision("Monster", { 40, 40 });

	SetHP(10);
	BodySettingBlood();
	SetAttackDelay(2.0f);
	AttackTimer_ = AttackDelay_;
}

void Gusher::MonsterUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		MoveDir_ = float4(GameEngineRandom::MainRandom->RandomFloat(-2, 2), GameEngineRandom::MainRandom->RandomFloat(-2, 2));
		MoveDir_.Normal2D();
		MoveDir_ *= GameEngineTime::GetDeltaTime() * MoveSpeed_;
	}

	MonsterSetMoveToWalk(MoveDir_);
	BodyUpdate(MoveDir_);
}

