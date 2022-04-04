#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro15 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro15();
	~Intro15();

	// delete Function
	Intro15(const Intro15& _Other) = delete;
	Intro15(Intro15&& _Other) noexcept = delete;
	Intro15& operator=(const Intro15& _Other) = delete;
	Intro15& operator=(Intro15&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

