#pragma once
#include "Monster.h"

enum class ClotState
{
	Default,
	Idle,
	Move,
	Attack,
	Max,
};

// Ό³Έν :
class Clot : public Monster
{
public:
	// constrcuter destructer
	Clot();
	~Clot();

	// delete Function
	Clot(const Clot& _Other) = delete;
	Clot(Clot&& _Other) noexcept = delete;
	Clot& operator=(const Clot& _Other) = delete;
	Clot& operator=(Clot&& _Other) noexcept = delete;

protected:

private:
	ClotState State_;
	float AnimTimer_;
	float4 MoveDir_;
	bool IsAttack_;

	void Start() override;
	void MonsterUpdate() override;
	void ChangeState(ClotState _State);
	void StateUpdate();

	void IdleStart();
	void MoveStart();
	void AttackStart();

	void IdleUpdate();
	void MoveUpdate();
	void AttackUpdate();
};

