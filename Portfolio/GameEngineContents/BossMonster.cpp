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
	HP_ -= _Damage;

	if (HP_ <= 0)
	{
		Room_->MinusMonsterCount();
		MonsterDeath();
	}
}
