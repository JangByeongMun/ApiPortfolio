#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro25 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro25();
	~Intro25();

	// delete Function
	Intro25(const Intro25& _Other) = delete;
	Intro25(Intro25&& _Other) noexcept = delete;
	Intro25& operator=(const Intro25& _Other) = delete;
	Intro25& operator=(Intro25&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* IsaacRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

