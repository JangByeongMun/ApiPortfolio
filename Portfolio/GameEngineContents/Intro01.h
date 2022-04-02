#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro01 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro01();
	~Intro01();

	// delete Function
	Intro01(const Intro01& _Other) = delete;
	Intro01(Intro01&& _Other) noexcept = delete;
	Intro01& operator=(const Intro01& _Other) = delete;
	Intro01& operator=(Intro01&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

