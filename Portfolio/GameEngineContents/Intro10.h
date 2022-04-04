#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro10 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro10();
	~Intro10();

	// delete Function
	Intro10(const Intro10& _Other) = delete;
	Intro10(Intro10&& _Other) noexcept = delete;
	Intro10& operator=(const Intro10& _Other) = delete;
	Intro10& operator=(Intro10&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

