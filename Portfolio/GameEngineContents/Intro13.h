#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro13 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro13();
	~Intro13();

	// delete Function
	Intro13(const Intro13& _Other) = delete;
	Intro13(Intro13&& _Other) noexcept = delete;
	Intro13& operator=(const Intro13& _Other) = delete;
	Intro13& operator=(Intro13&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

