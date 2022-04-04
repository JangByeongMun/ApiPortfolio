#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro20 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro20();
	~Intro20();

	// delete Function
	Intro20(const Intro20& _Other) = delete;
	Intro20(Intro20&& _Other) noexcept = delete;
	Intro20& operator=(const Intro20& _Other) = delete;
	Intro20& operator=(Intro20&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* DoorRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

