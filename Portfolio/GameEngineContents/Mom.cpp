#include "Mom.h"

Mom::Mom() 
{
}

Mom::~Mom() 
{
}

void Mom::Start()
{
	Type_ = BossType::Mom;
	SetHP(645.0f);
	SetAttackDelay(0.5f);

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

void Mom::MonsterUpdate()
{
}

void Mom::MonsterDeath()
{
}

void Mom::ChangeState(MomState _State)
{
}

void Mom::StateUpdate()
{
}

void Mom::IdleStart()
{
}

void Mom::HandStart()
{
}

void Mom::LegStart()
{
}

void Mom::SummonStart()
{
}

void Mom::DeadStart()
{
}

void Mom::IdleUpdate()
{
}

void Mom::HandUpdate()
{
}

void Mom::LegUpdate()
{
}

void Mom::SummonUpdate()
{
}

void Mom::DeadUpdate()
{
}
