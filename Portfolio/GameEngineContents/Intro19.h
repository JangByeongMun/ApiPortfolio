#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro19 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro19();
	~Intro19();

	// delete Function
	Intro19(const Intro19& _Other) = delete;
	Intro19(Intro19&& _Other) noexcept = delete;
	Intro19& operator=(const Intro19& _Other) = delete;
	Intro19& operator=(Intro19&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

