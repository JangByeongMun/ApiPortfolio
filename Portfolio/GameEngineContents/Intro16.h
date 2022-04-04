#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro16 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro16();
	~Intro16();

	// delete Function
	Intro16(const Intro16& _Other) = delete;
	Intro16(Intro16&& _Other) noexcept = delete;
	Intro16& operator=(const Intro16& _Other) = delete;
	Intro16& operator=(Intro16&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

