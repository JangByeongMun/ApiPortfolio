#pragma once
#include "Monster.h"

// Ό³Έν :
class Gut : public Monster
{
public:
	// constrcuter destructer
	Gut();
	~Gut();

	// delete Function
	Gut(const Gut& _Other) = delete;
	Gut(Gut&& _Other) noexcept = delete;
	Gut& operator=(const Gut& _Other) = delete;
	Gut& operator=(Gut&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MonsterUpdate() override;
};

