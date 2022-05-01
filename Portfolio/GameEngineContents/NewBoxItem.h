#pragma once
#include <GameEngine/GameEngineActor.h>

enum class NewBoxState
{
	Default,
	Appear,
	Idle,
	Open,
};

enum class NewBoxType
{
	Normal,
	Gold,
};

// Ό³Έν :
class NewBoxItem : public GameEngineActor
{
public:
	// constrcuter destructer
	NewBoxItem();
	~NewBoxItem();

	// delete Function
	NewBoxItem(const NewBoxItem& _Other) = delete;
	NewBoxItem(NewBoxItem&& _Other) noexcept = delete;
	NewBoxItem& operator=(const NewBoxItem& _Other) = delete;
	NewBoxItem& operator=(NewBoxItem&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;
	float AnimTimer_;
	NewBoxState State_;

	void Start() override;
	void Update();

	//////// FSM
	void ChangeState(NewBoxState _State);
	void AppearStart();
	void IdleStart();
	void AppearUpdate();
};

