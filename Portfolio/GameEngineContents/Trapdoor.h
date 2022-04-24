#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :
class Trapdoor : public GameEngineActor
{
public:
	// constrcuter destructer
	Trapdoor();
	~Trapdoor();

	// delete Function
	Trapdoor(const Trapdoor& _Other) = delete;
	Trapdoor(Trapdoor&& _Other) noexcept = delete;
	Trapdoor& operator=(const Trapdoor& _Other) = delete;
	Trapdoor& operator=(Trapdoor&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float AnimTimer_;
	bool IsOpen_;

	void Start() override;
	void Update() override;

public:
	void TurnOn(bool _On);
};

