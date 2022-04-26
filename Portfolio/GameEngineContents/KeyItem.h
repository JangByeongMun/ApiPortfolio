#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "ItemBase.h"

enum class KeyType
{
	None,
	Normal,
	Two,
	Master,
};

// Ό³Έν :
class KeyItem : public ItemBase
{
public:
	// constrcuter destructer
	KeyItem();
	~KeyItem();

	// delete Function
	KeyItem(const KeyItem& _Other) = delete;
	KeyItem(KeyItem&& _Other) noexcept = delete;
	KeyItem& operator=(const KeyItem& _Other) = delete;
	KeyItem& operator=(KeyItem&& _Other) noexcept = delete;

	void SetType(KeyType _Type);

protected:

private:
	KeyType Type_;
	GameEngineRenderer* Renderer_;

	void Update() override;
};

