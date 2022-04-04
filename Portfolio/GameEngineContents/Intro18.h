#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro18 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro18();
	~Intro18();

	// delete Function
	Intro18(const Intro18& _Other) = delete;
	Intro18(Intro18&& _Other) noexcept = delete;
	Intro18& operator=(const Intro18& _Other) = delete;
	Intro18& operator=(Intro18&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;
	bool Check3;
	bool Check4;
	bool Check5;
	float StartX;
	float CurrentX;
	bool IsLeft;

	void Start() override;
	void Update() override;
};

