#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ItemBase.h"

enum class BoxState
{
	Default,
	Appear,
	Idle,
	Open,
};

enum class BoxType
{
	Normal,
	Gold,
};

// Ό³Έν :
class BoxItem : public ItemBase
{
public:
	// constrcuter destructer
	BoxItem();
	~BoxItem();

	// delete Function
	BoxItem(const BoxItem& _Other) = delete;
	BoxItem(BoxItem&& _Other) noexcept = delete;
	BoxItem& operator=(const BoxItem& _Other) = delete;
	BoxItem& operator=(BoxItem&& _Other) noexcept = delete;

	void SetType(BoxType _Type);

protected:

private:
	GameEngineRenderer* Renderer_;
	BoxType Type_;
	float AnimTimer_;
	bool IsOpen_;
	bool IsSetting_;
	BoxState State_;

	void Start() override;
	void Update();

	void NormalBoxReward();
	void GoldBoxReward();

	//////// FSM
	void ChangeState(BoxState _State);
	void StateUpdate();

	void AppearStart();
	void IdleStart();
	void OpenStart();

	void AppearUpdate();
	void IdleUpdate();
	void OpenUpdate();
};

