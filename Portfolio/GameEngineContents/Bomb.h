#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>

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
	std::vector<GameEngineCollision*> CollisionResult_;
	GameEngineCollision* Collision_;
	float Timer_;
	float BombTime_;

	void Start() override;
	void Update() override;
};

