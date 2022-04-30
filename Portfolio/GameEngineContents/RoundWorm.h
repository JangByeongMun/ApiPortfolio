#pragma once
#include "Monster.h"

enum class RoundWormState
{
	Default,
	Idle,
	Hide,
	Show,
	Attack,
};

// Ό³Έν :
class RoundWorm : public Monster
{
public:
	// constrcuter destructer
	RoundWorm();
	~RoundWorm();

	// delete Function
	RoundWorm(const RoundWorm& _Other) = delete;
	RoundWorm(RoundWorm&& _Other) noexcept = delete;
	RoundWorm& operator=(const RoundWorm& _Other) = delete;
	RoundWorm& operator=(RoundWorm&& _Other) noexcept = delete;

protected:

private:
	RoundWormState State_;
	float AnimTimer_;
	bool IsAttack_;

	void MoveRandomPos();

	void Start() override;
	void MonsterUpdate() override;
	void ChangeState(RoundWormState _State);
	void StateUpdate();

	void IdleStart();
	void HideStart();
	void ShowStart();
	void AttackStart();

	void IdleUpdate();
	void HideUpdate();
	void ShowUpdate();
	void AttackUpdate();
};

