#pragma once
#include "Monster.h"

// Ό³Έν :
class Pooter : public Monster
{
public:
	Pooter();
	~Pooter();

	// delete Function
	Pooter(const Pooter& _Other) = delete;
	Pooter(Pooter&& _Other) noexcept = delete;
	Pooter& operator=(const Pooter& _Other) = delete;
	Pooter& operator=(Pooter&& _Other) noexcept = delete;

protected:

private:
	bool IsAttackAnim;

	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;
	void Attack();
};

