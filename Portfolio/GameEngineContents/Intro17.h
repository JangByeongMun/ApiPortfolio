#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro17 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro17();
	~Intro17();

	// delete Function
	Intro17(const Intro17& _Other) = delete;
	Intro17(Intro17&& _Other) noexcept = delete;
	Intro17& operator=(const Intro17& _Other) = delete;
	Intro17& operator=(Intro17&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	float StartX;
	float CurrentX;
	bool IsLeft;

	void Start() override;
	void Update() override;
};

