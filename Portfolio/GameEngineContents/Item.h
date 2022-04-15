#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include "ContentsEnum.h"

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

	void SetType(ItemType _Type);
	ItemType GetType();

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	GameEngineCollision* Collision_;
	ItemType Type_;

	void Start() override;
	void Update() override;
};

