#include "Gaper.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "Gusher.h"
#include "RoomActor.h"

Gaper::Gaper() 
	: AnimTimer_(0.0f)
	, IsChange_(false)
{
}

Gaper::~Gaper() 
{
}

void Gaper::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);
	Renderer_->CreateAnimation("monster_017_gaper.bmp", "Idle", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_017_gaper.bmp", "StartChase1", 0, 1, 0.1f, false);
	Renderer_->CreateAnimation("monster_017_gaper.bmp", "StartChase2", 2, 3, 0.1f, false);
	Renderer_->ChangeAnimation("Idle");

	Collision_ = CreateCollision("Monster", { 40, 40 }, { 0, 10 });

	SetHP(10);
	BodySetting();
	SetMoveSpeed(100.0f);
}

void Gaper::MonsterUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 1.5f && IsChange_ == false)
	{
		IsChange_ = true;
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 2);
		std::string TmpName = "StartChase" + std::to_string(RandomInt);
		Renderer_->ChangeAnimation(TmpName);
	}

	float4 MoveFloat4 = AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime();
	MonsterSetMoveToWalk(MoveFloat4);
	BodyUpdate(MoveFloat4);
}

void Gaper::MonsterDeath()
{
	float RandomFloat = GameEngineRandom::MainRandom->RandomFloat(0.0f, 1.0f);
	if (RandomFloat <= 0.5f)
	{
		Gusher* TmpMonster = GetLevel()->CreateActor<Gusher>();
		TmpMonster->SetPosition(GetPosition());
		TmpMonster->SetRoom(*GetRoom());
		TmpMonster->SetMoveSpeed(100.0f);
		GetRoom()->AddMonster(TmpMonster);
		GetRoom()->AddMonsterCount();
	}
}
