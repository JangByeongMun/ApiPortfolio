#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

// Ό³Έν :
class ShopItem : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopItem();
	~ShopItem();

	// delete Function
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(ShopItem&& _Other) noexcept = delete;
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(ShopItem&& _Other) noexcept = delete;

	void SetType(ShopType _Type);

protected:

private:
	ShopType Type_;
	GameEngineCollision* Collision_;
	std::vector<GameEngineRenderer*> RendererVector_;

	void Update() override;
};

