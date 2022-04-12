#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :
class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	Item(float4 _Scale);
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* Collision_;

	void Update() override;
	virtual void AddToPlayer() = 0;
};

