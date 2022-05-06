#include "Boil.h"

Boil::Boil() 
{
}

Boil::~Boil() 
{
}

void Boil::Start()
{
	Renderer_ = CreateRenderer("monster_087_boil.bmp", static_cast<int>(ORDER::PLAYER));
	Collision_ = CreateCollision("Monster", { 60, 60 });

	SetHP(20.0f);
	Damaged(15.0f);
	SetMoveSpeed(0.0f);
	SetAttackDelay(3.0f);
}

void Boil::MonsterUpdate()
{
	if (GetHP() < 20.0f)
	{
		Heal(5.0f * GameEngineTime::GetDeltaTime());
	}
	else
	{
		AttackTimer_ += GameEngineTime::GetDeltaTime();
		if (AttackTimer_ >= AttackDelay_)
		{
			AttackTimer_ = 0.0f;
			for (int i = 0; i < 4; i++)
			{
				float4 RandomPos = AttackNormalDir() * 350.0f;
				RandomPos += float4(GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f), GameEngineRandom::MainRandom->RandomFloat(-2.0f, 2.0f)) * 60;
				Shoot(RandomPos, ProjectileType::ENEMY_BASIC);
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (2.0f * i <= GetHP() && GetHP() < 2.0f * (i + 1))
		{
			Renderer_->SetIndex(9 - i);
		}
	}
}
