#pragma once
#include "BodyMonster.h"

// Ό³Έν :
class Mulliboom : public BodyMonster
{
public:
	// constrcuter destructer
	Mulliboom();
	~Mulliboom();

	// delete Function
	Mulliboom(const Mulliboom& _Other) = delete;
	Mulliboom(Mulliboom&& _Other) noexcept = delete;
	Mulliboom& operator=(const Mulliboom& _Other) = delete;
	Mulliboom& operator=(Mulliboom&& _Other) noexcept = delete;

protected:

private:
	float AnimTimer_;
	bool IsChange_;

	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;
};

