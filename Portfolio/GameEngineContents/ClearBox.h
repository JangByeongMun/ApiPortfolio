#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class ClearBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ClearBox();
	~ClearBox();

	// delete Function
	ClearBox(const ClearBox& _Other) = delete;
	ClearBox(ClearBox&& _Other) noexcept = delete;
	ClearBox& operator=(const ClearBox& _Other) = delete;
	ClearBox& operator=(ClearBox&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float AnimTimer_;

	void Start() override;
	void Update() override;
};

