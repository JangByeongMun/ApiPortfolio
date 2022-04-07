#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Shooter.h"

enum class PlayerBodyState
{
	Idle,
	Move
};

enum class PlayerHeadState
{
	Idle,
	Attack
};

// 설명 : 플레이어
class GameEngineImage;
class Player : public Shooter
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	
private:
	float Speed_;
	GameEngineRenderer* BodyRender_;
	GameEngineRenderer* HeadRender_;
	GameEngineCollision* PlayerCollision;
	GameEngineImage* MapColImage_;

	std::string BodyAnimationName;
	std::string HeadAnimationName;

	void Start() override;
	void Update() override;
	void CollisionCheck();
	void PlayerSetMove(float4 _Value);

///////////////////////////////// FSM
private:
	PlayerBodyState CurBody_;
	PlayerHeadState CurHead_;
	float4 MoveDir_;

	bool IsMoveKey();
	bool IsAttackKey();

public:
	void ChangeBodyState(PlayerBodyState _State);
	void ChangeHeadState(PlayerHeadState _State);
	void StateUpdate();

private: 
	void BodyIdleStart();
	void BodyMoveStart();
	void HeadIdleStart();
	void HeadAttackStart();

	void BodyIdleUpdate();
	void BodyMoveUpdate();
	void HeadIdleUpdate();
	void HeadAttackUpdate();

///////////////////////////////// 공격속도
	float AttackSpeed_;
	float ShotSpeed_;

	float NextAttackTime_;
	float CurrentAttackTime_;
};

