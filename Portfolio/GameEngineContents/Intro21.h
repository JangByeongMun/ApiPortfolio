#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro21 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro21();
	~Intro21();

	// delete Function
	Intro21(const Intro21& _Other) = delete;
	Intro21(Intro21&& _Other) noexcept = delete;
	Intro21& operator=(const Intro21& _Other) = delete;
	Intro21& operator=(Intro21&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

