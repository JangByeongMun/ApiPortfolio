#pragma once
#include "Monster.h"

// Ό³Έν :
class Gaper : public Monster
{
public:
	// constrcuter destructer
	Gaper();
	~Gaper();

	// delete Function
	Gaper(const Gaper& _Other) = delete;
	Gaper(Gaper&& _Other) noexcept = delete;
	Gaper& operator=(const Gaper& _Other) = delete;
	Gaper& operator=(Gaper&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MonsterUpdate() override;
	void Attack();
};

