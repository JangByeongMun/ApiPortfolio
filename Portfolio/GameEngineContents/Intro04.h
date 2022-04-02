#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro04 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro04();
	~Intro04();

	// delete Function
	Intro04(const Intro04& _Other) = delete;
	Intro04(Intro04&& _Other) noexcept = delete;
	Intro04& operator=(const Intro04& _Other) = delete;
	Intro04& operator=(Intro04&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

