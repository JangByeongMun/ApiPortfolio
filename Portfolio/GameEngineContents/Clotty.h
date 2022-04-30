#pragma once
#include "Monster.h"

enum class ClottyState
{
	Default,
	Idle,
	Move, 
	Attack,
	Max,
};

// Ό³Έν :
class Clotty : public Monster
{
public:
	// constrcuter destructer
	Clotty();
	~Clotty();

	// delete Function
	Clotty(const Clotty& _Other) = delete;
	Clotty(Clotty&& _Other) noexcept = delete;
	Clotty& operator=(const Clotty& _Other) = delete;
	Clotty& operator=(Clotty&& _Other) noexcept = delete;

protected:

private:
	ClottyState State_;
	float AnimTimer_;
	float4 MoveDir_;
	bool IsAttack_;

	void Start() override;
	void MonsterUpdate() override;
	void ChangeState(ClottyState _State);
	void StateUpdate();

	void IdleStart();
	void MoveStart();
	void AttackStart();

	void IdleUpdate();
	void MoveUpdate();
	void AttackUpdate();
};

