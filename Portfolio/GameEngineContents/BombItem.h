#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "ItemBase.h"

enum class BombType
{
	None,
	Normal,
	Two,
};

// Ό³Έν :
class BombItem : public ItemBase
{
public:
	// constrcuter destructer
	BombItem();
	~BombItem();

	// delete Function
	BombItem(const BombItem& _Other) = delete;
	BombItem(BombItem&& _Other) noexcept = delete;
	BombItem& operator=(const BombItem& _Other) = delete;
	BombItem& operator=(BombItem&& _Other) noexcept = delete;

	void SetType(BombType _Type);

protected:

private:
	BombType Type_;
	GameEngineRenderer* Renderer_;
	bool IsSetting_;

	void Update() override;
};

