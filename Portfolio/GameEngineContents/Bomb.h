#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include "ItemBase.h"

// Ό³Έν :
class Bomb : public ItemBase
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

	void Boom();

protected:

private:
	GameEngineRenderer* Renderer_;

	float Timer_;
	float BombTime_;
	bool IsExplode;

	void Start() override;
	void Update() override;
	void BompAnimation();
};

