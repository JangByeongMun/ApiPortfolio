#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class BlackHeartEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BlackHeartEffect();
	~BlackHeartEffect();

	// delete Function
	BlackHeartEffect(const BlackHeartEffect& _Other) = delete;
	BlackHeartEffect(BlackHeartEffect&& _Other) noexcept = delete;
	BlackHeartEffect& operator=(const BlackHeartEffect& _Other) = delete;
	BlackHeartEffect& operator=(BlackHeartEffect&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;
	float AnimTimer_;
	bool IsDestroy_;
	float4 StartPos_;

	void Start();
	void Update();
};

