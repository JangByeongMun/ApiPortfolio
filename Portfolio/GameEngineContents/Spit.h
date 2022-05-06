#pragma once
#include "Monster.h"

// ���� :
class Spit : public Monster
{
public:
	// constrcuter destructer
	Spit();
	~Spit();

	// delete Function
	Spit(const Spit& _Other) = delete;
	Spit(Spit&& _Other) noexcept = delete;
	Spit& operator=(const Spit& _Other) = delete;
	Spit& operator=(Spit&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;

};