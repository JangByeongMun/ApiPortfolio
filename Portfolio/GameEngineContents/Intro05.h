#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

class Intro05 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro05();
	~Intro05();

	// delete Function
	Intro05(const Intro05& _Other) = delete;
	Intro05(Intro05&& _Other) noexcept = delete;
	Intro05& operator=(const Intro05& _Other) = delete;
	Intro05& operator=(Intro05&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* MomRenderer;
	GameEngineRenderer* IsaacRenderer;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

