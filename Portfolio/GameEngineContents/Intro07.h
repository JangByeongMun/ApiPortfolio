#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro07 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro07();
	~Intro07();

	// delete Function
	Intro07(const Intro07& _Other) = delete;
	Intro07(Intro07&& _Other) noexcept = delete;
	Intro07& operator=(const Intro07& _Other) = delete;
	Intro07& operator=(Intro07&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;

	void Start() override;
};

