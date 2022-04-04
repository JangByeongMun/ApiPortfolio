#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro12 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro12();
	~Intro12();

	// delete Function
	Intro12(const Intro12& _Other) = delete;
	Intro12(Intro12&& _Other) noexcept = delete;
	Intro12& operator=(const Intro12& _Other) = delete;
	Intro12& operator=(Intro12&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* DoorRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

