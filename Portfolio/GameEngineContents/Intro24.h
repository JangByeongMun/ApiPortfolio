#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro24 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro24();
	~Intro24();

	// delete Function
	Intro24(const Intro24& _Other) = delete;
	Intro24(Intro24&& _Other) noexcept = delete;
	Intro24& operator=(const Intro24& _Other) = delete;
	Intro24& operator=(Intro24&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* DoorRenderer_;
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;
	bool Check3;

	void Start() override;
	void Update() override;
};

