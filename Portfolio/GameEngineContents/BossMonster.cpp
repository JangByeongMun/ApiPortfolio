#include "BossMonster.h"
#include "RoomActor.h"

BossMonster::BossMonster() 
	: Type_(BossType::Default)
{
}

BossMonster::~BossMonster() 
{
}

void BossMonster::Damaged(float _Damage)
{
	if (HP_ <= 0)
	{
		return;
	}

	HP_ -= _Damage;

	SetHPUI();
	if (HP_ <= 0)
	{
		Room_->MinusBossCount();
		MonsterDeath();
	}
}

void BossMonster::SetHPUI()
{
	Room_->SetBossHPUI(HP_ / MaxHP_);
}
