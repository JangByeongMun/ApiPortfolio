#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class SpacebarUI : public GameEngineActor
{
public:
	// constrcuter destructer
	SpacebarUI();
	~SpacebarUI();

	// delete Function
	SpacebarUI(const SpacebarUI& _Other) = delete;
	SpacebarUI(SpacebarUI&& _Other) noexcept = delete;
	SpacebarUI& operator=(const SpacebarUI& _Other) = delete;
	SpacebarUI& operator=(SpacebarUI&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* ItemRenderer;

	void Start() override;
};

