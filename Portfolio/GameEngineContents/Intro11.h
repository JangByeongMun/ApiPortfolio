#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Intro11 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro11();
	~Intro11();

	// delete Function
	Intro11(const Intro11& _Other) = delete;
	Intro11(Intro11&& _Other) noexcept = delete;
	Intro11& operator=(const Intro11& _Other) = delete;
	Intro11& operator=(Intro11&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* FaceRenderer_;
	float ActorTime_;
	bool Check1;
	bool Check2;

	void Start() override;
	void Update() override;
};

