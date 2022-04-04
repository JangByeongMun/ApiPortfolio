#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Intro08 : public GameEngineActor
{
public:
	// constrcuter destructer
	Intro08();
	~Intro08();

	// delete Function
	Intro08(const Intro08& _Other) = delete;
	Intro08(Intro08&& _Other) noexcept = delete;
	Intro08& operator=(const Intro08& _Other) = delete;
	Intro08& operator=(Intro08&& _Other) noexcept = delete;

protected:

private:
	float ActorTime_;

	void Start() override;
};

