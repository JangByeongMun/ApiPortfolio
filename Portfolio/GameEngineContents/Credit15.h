#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit15 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit15();
	~Credit15();

	// delete Function
	Credit15(const Credit15& _Other) = delete;
	Credit15(Credit15&& _Other) noexcept = delete;
	Credit15& operator=(const Credit15& _Other) = delete;
	Credit15& operator=(Credit15&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;

	void Start() override;
	void Update() override;
};

