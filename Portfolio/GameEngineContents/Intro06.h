#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

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
	GameEngineRenderer* FaceRenderer_;
	float ActorTime_;
	bool Check1;

	void Start() override;
	void Update() override;
};

