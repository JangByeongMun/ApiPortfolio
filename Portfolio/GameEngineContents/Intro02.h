#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro02 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro02();
	~Intro02();

	// delete Function
	Intro02(const Intro02& _Other) = delete;
	Intro02(Intro02&& _Other) noexcept = delete;
	Intro02& operator=(const Intro02& _Other) = delete;
	Intro02& operator=(Intro02&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

