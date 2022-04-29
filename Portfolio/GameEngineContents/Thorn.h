#pragma once
#include <GameEngine/GameEngineActor.h>

enum class ThornType
{
	Default,
	Always,
	Anim,
};

// Ό³Έν :
class Thorn : public GameEngineActor
{
public:
	// constrcuter destructer
	Thorn();
	~Thorn();

	// delete Function
	Thorn(const Thorn& _Other) = delete;
	Thorn(Thorn&& _Other) noexcept = delete;
	Thorn& operator=(const Thorn& _Other) = delete;
	Thorn& operator=(Thorn&& _Other) noexcept = delete;

	void SetType(ThornType _Type);

protected:

private:
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* ShadowRenderer_;
	GameEngineCollision* Collision_;
	ThornType Type_;

	void Update() override;
};

