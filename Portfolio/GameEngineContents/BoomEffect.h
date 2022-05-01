#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class BoomEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BoomEffect();
	~BoomEffect();

	// delete Function
	BoomEffect(const BoomEffect& _Other) = delete;
	BoomEffect(BoomEffect&& _Other) noexcept = delete;
	BoomEffect& operator=(const BoomEffect& _Other) = delete;
	BoomEffect& operator=(BoomEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void MakeEffect();
};

