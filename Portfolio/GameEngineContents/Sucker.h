#pragma once
#include "Monster.h"

// Ό³Έν :
class Sucker : public Monster
{
public:
	// constrcuter destructer
	Sucker();
	~Sucker();

	// delete Function
	Sucker(const Sucker& _Other) = delete;
	Sucker(Sucker&& _Other) noexcept = delete;
	Sucker& operator=(const Sucker& _Other) = delete;
	Sucker& operator=(Sucker&& _Other) noexcept = delete;

protected:

private:

	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;
};

