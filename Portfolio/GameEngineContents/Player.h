#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Shooter.h"

// 설명 : 플레이어
class Player : public GameEngineActor, public Shooter
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
	void Start() override;
	void Update() override;
	void Render() override;
};

