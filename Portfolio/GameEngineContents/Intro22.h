#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro22 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro22();
	~Intro22();

	// delete Function
	Intro22(const Intro22& _Other) = delete;
	Intro22(Intro22&& _Other) noexcept = delete;
	Intro22& operator=(const Intro22& _Other) = delete;
	Intro22& operator=(Intro22&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* DoorRenderer_;
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

