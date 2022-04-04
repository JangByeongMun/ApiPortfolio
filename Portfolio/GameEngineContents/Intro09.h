#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro09 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro09();
	~Intro09();

	// delete Function
	Intro09(const Intro09& _Other) = delete;
	Intro09(Intro09&& _Other) noexcept = delete;
	Intro09& operator=(const Intro09& _Other) = delete;
	Intro09& operator=(Intro09&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;
	bool Check3;
	bool Check4;

	void Start() override;
	void Update() override;
};

