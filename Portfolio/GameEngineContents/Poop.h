#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Poop : public GameEngineActor
{
public:
	// constrcuter destructer
	Poop();
	~Poop();

	// delete Function
	Poop(const Poop& _Other) = delete;
	Poop(Poop&& _Other) noexcept = delete;
	Poop& operator=(const Poop& _Other) = delete;
	Poop& operator=(Poop&& _Other) noexcept = delete;
	
	void AddHp(float _Value);

protected:

private:
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float CurrentHP_;

	void Start() override;
	void RandomDrop();
};

