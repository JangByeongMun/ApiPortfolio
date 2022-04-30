#pragma once
#include "BodyMonster.h"

// Ό³Έν :
class Gusher : public BodyMonster
{
public:
	// constrcuter destructer
	Gusher();
	~Gusher();

	// delete Function
	Gusher(const Gusher& _Other) = delete;
	Gusher(Gusher&& _Other) noexcept = delete;
	Gusher& operator=(const Gusher& _Other) = delete;
	Gusher& operator=(Gusher&& _Other) noexcept = delete;

protected:

private:
	float4 MoveDir_;

	void Start() override;
	void MonsterUpdate() override;
};

