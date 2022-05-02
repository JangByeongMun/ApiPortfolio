#pragma once
#include "BossMonster.h"

enum class MomState
{
	Idle = 0,
	Hand,
	Leg,
	Summon,
	Dead,
};

// Ό³Έν :
class Mom : public BossMonster
{
public:
	// constrcuter destructer
	Mom();
	~Mom();

	// delete Function
	Mom(const Mom& _Other) = delete;
	Mom(Mom&& _Other) noexcept = delete;
	Mom& operator=(const Mom& _Other) = delete;
	Mom& operator=(Mom&& _Other) noexcept = delete;

protected:

private:
	MomState State_;
	std::vector<GameEngineRenderer*> DoorRenderers_;
	std::vector<GameEngineRenderer*> EyeRenderers_;
	std::vector<GameEngineRenderer*> HandRenderers_;

	GameEngineRenderer* LegRenderer_;
	GameEngineRenderer* LegShadowRenderer_;
	GameEngineCollision* LegCollision_;

	std::vector<GameEngineCollision*> EyeCollision_;
	std::vector<GameEngineCollision*> HandCollision_;
	std::vector<GameEngineCollision*> HandCheckCollision_;
	float AnimTimer_;
	bool IsAnim_;
	int HandCheck_;

	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;
	void ChangeState(MomState _State);
	void StateUpdate();

	void IdleStart();
	void HandStart();
	void LegStart();
	void SummonStart();
	void DeadStart();

	void IdleUpdate();
	void HandUpdate();
	void LegUpdate();
	void SummonUpdate();
	void DeadUpdate();

	void ResetValue();
	int HandCheck();
};

