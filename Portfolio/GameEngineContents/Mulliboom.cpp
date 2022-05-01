#include "Mulliboom.h"
#include "BoomEffect.h"

Mulliboom::Mulliboom() 
{
}

Mulliboom::~Mulliboom() 
{
}

void Mulliboom::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);
	Renderer_->CreateAnimation("monster_061_muliboom.bmp", "Idle", 0, 2, 0.2f, true);
	Renderer_->ChangeAnimation("Idle");
	Renderer_->SetPivot({0, -10});

	Collision_ = CreateCollision("Monster", { 40, 40 });

	SetHP(13);
	BodySettingBlood();
	SetMoveSpeed(100.0f);
}

void Mulliboom::MonsterUpdate()
{
	float4 MoveFloat4 = AttackNormalDir() * MoveSpeed_ * GameEngineTime::GetDeltaTime();
	MonsterSetMoveToWalk(MoveFloat4);
	BodyUpdate(MoveFloat4);
}

void Mulliboom::MonsterDeath()
{
	Collision_->Off();
	GetLevel()->CreateActor<BoomEffect>()->Setting(GetPosition());
}