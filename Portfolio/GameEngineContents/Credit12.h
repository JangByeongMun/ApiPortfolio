#pragma once
#include <GameEngine/GameEngineActor.h>

class Credit12 : public GameEngineActor
{
public:
	// constrcuter destructer
	Credit12();
	~Credit12();

	// delete Function
	Credit12(const Credit12& _Other) = delete;
	Credit12(Credit12&& _Other) noexcept = delete;
	Credit12& operator=(const Credit12& _Other) = delete;
	Credit12& operator=(Credit12&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* BookRenderer_;
	float ActorTime_;

	void Start() override;
	void Update() override;
};

