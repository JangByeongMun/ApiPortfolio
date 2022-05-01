#pragma once
#include "Monster.h"

enum class HostType
{
	Normal,
	Red,
};

enum class HostState
{
	Idle,
	Attack,
};

// Ό³Έν :
class Host : public Monster
{
public:
	// constrcuter destructer
	Host();
	~Host();

	// delete Function
	Host(const Host& _Other) = delete;
	Host(Host&& _Other) noexcept = delete;
	Host& operator=(const Host& _Other) = delete;
	Host& operator=(Host&& _Other) noexcept = delete;
	
	void SetType(HostType _Type);

protected:

private:
	HostType Type_;
	HostState State_;
	float AnimTimer_;

	void Start() override;
	void MonsterUpdate() override;

	void ChangeState(HostState _State);
	void StateUpdate();

	void IdleStart();
	void AttackStart();

	void IdleUpdate();
	void AttackUpdate();
};

