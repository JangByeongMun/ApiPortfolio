#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Hole : public GameEngineActor
{
public:
	// constrcuter destructer
	Hole();
	~Hole();

	// delete Function
	Hole(const Hole& _Other) = delete;
	Hole(Hole&& _Other) noexcept = delete;
	Hole& operator=(const Hole& _Other) = delete;
	Hole& operator=(Hole&& _Other) noexcept = delete;

	void Setting(int _Index);

protected:

private:
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	int HoleIndex_;

};

