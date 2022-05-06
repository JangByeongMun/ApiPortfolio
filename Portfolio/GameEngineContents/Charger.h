#pragma once
#include "Monster.h"

enum class ChargerDir
{
	None,
	Up,
	Down,
	Left,
	Right,
};

// Ό³Έν :
class Charger : public Monster
{
public:
	// constrcuter destructer
	Charger();
	~Charger();

	// delete Function
	Charger(const Charger& _Other) = delete;
	Charger(Charger&& _Other) noexcept = delete;
	Charger& operator=(const Charger& _Other) = delete;
	Charger& operator=(Charger&& _Other) noexcept = delete;

protected:

private:
	bool IsAttack_;
	ChargerDir Dir_;
	float4 MoveDir_;
	float AnimTimer_;

	void Start() override;
	void MonsterUpdate() override;
	ChargerDir PlayerLine();
};

