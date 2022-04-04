#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro23 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro23();
	~Intro23();

	// delete Function
	Intro23(const Intro23& _Other) = delete;
	Intro23(Intro23&& _Other) noexcept = delete;
	Intro23& operator=(const Intro23& _Other) = delete;
	Intro23& operator=(Intro23&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* DoorRenderer_;
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

