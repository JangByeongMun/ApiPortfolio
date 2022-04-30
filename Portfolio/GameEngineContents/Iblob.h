#pragma once
#include "Monster.h"

enum class IblobState
{
	Default,
	Idle,
	Move,
	Attack,
	Max,
};

// Ό³Έν :
class Iblob : public Monster
{
public:
	// constrcuter destructer
	Iblob();
	~Iblob();

	// delete Function
	Iblob(const Iblob& _Other) = delete;
	Iblob(Iblob&& _Other) noexcept = delete;
	Iblob& operator=(const Iblob& _Other) = delete;
	Iblob& operator=(Iblob&& _Other) noexcept = delete;

protected:

private:
	IblobState State_;
	float AnimTimer_;
	float4 MoveDir_;
	bool IsAttack_;

	void Start() override;
	void MonsterUpdate() override;
	void ChangeState(IblobState _State);
	void StateUpdate();

	void IdleStart();
	void MoveStart();
	void AttackStart();

	void IdleUpdate();
	void MoveUpdate();
	void AttackUpdate();
};

