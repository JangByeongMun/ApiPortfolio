#pragma once
#include "BodyMonster.h"

// Ό³Έν :
class Gaper : public BodyMonster
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
	float AnimTimer_;
	bool IsChange_;

	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;
};

