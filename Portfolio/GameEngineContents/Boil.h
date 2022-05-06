#pragma once
#include "Monster.h"

// Ό³Έν :
class Boil : public Monster
{
public:
	// constrcuter destructer
	Boil();
	~Boil();

	// delete Function
	Boil(const Boil& _Other) = delete;
	Boil(Boil&& _Other) noexcept = delete;
	Boil& operator=(const Boil& _Other) = delete;
	Boil& operator=(Boil&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MonsterUpdate() override;
};

