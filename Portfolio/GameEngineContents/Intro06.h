#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro06 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro06();
	~Intro06();

	// delete Function
	Intro06(const Intro06& _Other) = delete;
	Intro06(Intro06&& _Other) noexcept = delete;
	Intro06& operator=(const Intro06& _Other) = delete;
	Intro06& operator=(Intro06&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

