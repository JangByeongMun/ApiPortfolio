#pragma once
#include "BossMonster.h"

enum class LokiState
{
	Idle = 0,
	Jump,
	ShootOnce,
	ShootTriple,
	Summon,
	Dead,
};

// Ό³Έν :
class Loki : public BossMonster
{
public:
	// constrcuter destructer
	Loki();
	~Loki();

	// delete Function
	Loki(const Loki& _Other) = delete;
	Loki(Loki&& _Other) noexcept = delete;
	Loki& operator=(const Loki& _Other) = delete;
	Loki& operator=(Loki&& _Other) noexcept = delete;

protected:

private:
	LokiState State_;
	float AnimTimer_;
	bool IsAnim_;
	GameEngineRenderer* ShadowRenderer_;

	void MoveRandomPos();

	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;
	void ChangeState(LokiState _State);
	void StateUpdate();

	void IdleStart();
	void JumpStart();
	void ShootOnceStart();
	void ShootTripleStart();
	void SummonStart();
	void DeadStart();

	void IdleUpdate();
	void JumpUpdate();
	void ShootOnceUpdate();
	void ShootTripleUpdate();
	void SummonUpdate();
	void DeadUpdate();
};

