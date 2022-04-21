#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class RandomBlood : public GameEngineActor
{
public:
	// constrcuter destructer
	RandomBlood();
	~RandomBlood();

	// delete Function
	RandomBlood(const RandomBlood& _Other) = delete;
	RandomBlood(RandomBlood&& _Other) noexcept = delete;
	RandomBlood& operator=(const RandomBlood& _Other) = delete;
	RandomBlood& operator=(RandomBlood&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Renderer_;
	float4 Dir_;

	void Start() override;
	void Update() override;
};

