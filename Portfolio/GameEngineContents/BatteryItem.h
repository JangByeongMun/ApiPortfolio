#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "ItemBase.h"

// Ό³Έν :
class BatteryItem : public ItemBase
{
public:
	// constrcuter destructer
	BatteryItem();
	~BatteryItem();

	// delete Function
	BatteryItem(const BatteryItem& _Other) = delete;
	BatteryItem(BatteryItem&& _Other) noexcept = delete;
	BatteryItem& operator=(const BatteryItem& _Other) = delete;
	BatteryItem& operator=(BatteryItem&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

