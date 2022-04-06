#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Shooter.h"

enum class PlayerMoveDir
{
	Idle,
	Left,
	Right,
	Up,
	Down,
};

enum class PlayerAttackDir
{
	Idle,
	Left,
	Right,
	Up,
	Down,
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

	PlayerMoveDir CurMove_;
	PlayerAttackDir CurAttack_;

	std::string MoveAnimationName;
	std::string AttackAnimationName;

	// 공격
	float AttackSpeed_;
	float NextAttackTime_;
	float CurrentAttackTime_;

	void Start() override;
	void Update() override;
	void Render() override;

	void CollisionCheck();
	void AttackCheck();
};

