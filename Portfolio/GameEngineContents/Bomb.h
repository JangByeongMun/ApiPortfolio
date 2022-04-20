#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :
class Bomb : public GameEngineActor
{
public:
	// constrcuter destructer
	Bomb();
	~Bomb();

	// delete Function
	Bomb(const Bomb& _Other) = delete;
	Bomb(Bomb&& _Other) noexcept = delete;
	Bomb& operator=(const Bomb& _Other) = delete;
	Bomb& operator=(Bomb&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* Collision_;
	GameEngineRenderer* Renderer_;

	float Timer_;
	float BombTime_;

	void Start() override;
	void Update() override;
	void BompAnimation();
};

