#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro03 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro03();
	~Intro03();

	// delete Function
	Intro03(const Intro03& _Other) = delete;
	Intro03(Intro03&& _Other) noexcept = delete;
	Intro03& operator=(const Intro03& _Other) = delete;
	Intro03& operator=(Intro03&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

