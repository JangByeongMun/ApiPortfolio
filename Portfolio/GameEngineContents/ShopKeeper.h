#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν :
class ShopKeeper : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopKeeper();
	~ShopKeeper();

	// delete Function
	ShopKeeper(const ShopKeeper& _Other) = delete;
	ShopKeeper(ShopKeeper&& _Other) noexcept = delete;
	ShopKeeper& operator=(const ShopKeeper& _Other) = delete;
	ShopKeeper& operator=(ShopKeeper&& _Other) noexcept = delete;

	void DeadAnim();

protected:

private:
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	bool IsDead_;

	void Start() override;
};

