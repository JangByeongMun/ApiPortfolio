#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Shooter.h"

// 설명 : 플레이어
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

	void Start() override;
	void Update() override;
	void Render() override;

	void CollisionCheck();
};

