#pragma once
#include "Monster.h"

// Ό³Έν :
class BossMonster : public Monster
{
public:
	// constrcuter destructer
	BossMonster();
	~BossMonster();

	// delete Function
	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

protected:
	BossType Type_;

	void Damaged(float _Damage) override;
	void SetHPUI();
};

