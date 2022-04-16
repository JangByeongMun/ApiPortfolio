#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

enum class MoneyType
{
	None,
	Normal,
	Black,
	Silver,
};

// Ό³Έν :
class MoneyItem : public GameEngineActor
{
public:
	// constrcuter destructer
	MoneyItem();
	~MoneyItem();

	// delete Function
	MoneyItem(const MoneyItem& _Other) = delete;
	MoneyItem(MoneyItem&& _Other) noexcept = delete;
	MoneyItem& operator=(const MoneyItem& _Other) = delete;
	MoneyItem& operator=(MoneyItem&& _Other) noexcept = delete;
	
	void SetType(MoneyType _Type);

protected:

private:
	MoneyType Type_;
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* ShadowRenderer_;
	GameEngineCollision* Collision_;

	void Update() override;
};

