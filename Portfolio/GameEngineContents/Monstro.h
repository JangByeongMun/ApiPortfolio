#pragma once
#include "BossMonster.h"

enum class MonstroState
{
	Idle = 0,
	LargeJump,
	SmallJump,
	Attack,
	Dead,
};

// Ό³Έν :
class Monstro : public BossMonster
{
public:
	// constrcuter destructer
	Monstro();
	~Monstro();

	// delete Function
	Monstro(const Monstro& _Other) = delete;
	Monstro(Monstro&& _Other) noexcept = delete;
	Monstro& operator=(const Monstro& _Other) = delete;
	Monstro& operator=(Monstro&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;

///////////////////////////////// FSM
private:
	MonstroState State_;
	std::string RendererName_Left;
	std::string RendererName_Right;
	float AnimTimer_;
	bool IsAnim_;

	void StateUpdate();

	void IdleStart();
	void LargeJumpStart();
	void SmallJumpStart();
	void AttackStart();
	void DeadStart();

	void IdleUpdate();
	void LargeJumpUpdate();
	void SmallJumpUpdate();
	void AttackUpdate();
	void DeadUpdate();

public:
	void ChangeState(MonstroState _State);
	inline void ChangeMonstroAnimation(std::string _Name)
	{
		if (IsLeft_)
		{
			Renderer_->ChangeAnimation(RendererName_Left + _Name);
		}
		else
		{
			Renderer_->ChangeAnimation(RendererName_Right + _Name);
		}
	}
};

