#pragma once
#include "ItemBase.h"

enum class HeartType
{
	Default,
	Red,
	RedHalf,
	RedTwo,
	Soul,
	SoulHalf,
	Black,
	BlackHalf,
	Max,
};

// Ό³Έν :
class HeartItem : public ItemBase
{
public:
	// constrcuter destructer
	HeartItem();
	~HeartItem();

	// delete Function
	HeartItem(const HeartItem& _Other) = delete;
	HeartItem(HeartItem&& _Other) noexcept = delete;
	HeartItem& operator=(const HeartItem& _Other) = delete;
	HeartItem& operator=(HeartItem&& _Other) noexcept = delete;

	void Setting(HeartType _Type);

protected:

private:
	HeartType Type_;
	GameEngineRenderer* Renderer_;

	void Update() override;
};

