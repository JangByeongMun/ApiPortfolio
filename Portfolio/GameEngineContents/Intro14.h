#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro14 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro14();
	~Intro14();

	// delete Function
	Intro14(const Intro14& _Other) = delete;
	Intro14(Intro14&& _Other) noexcept = delete;
	Intro14& operator=(const Intro14& _Other) = delete;
	Intro14& operator=(Intro14&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* MomRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

