#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

// Ό³Έν :
class HpUI : public GameEngineActor
{
public:
	// constrcuter destructer
	HpUI();
	~HpUI();

	// delete Function
	HpUI(const HpUI& _Other) = delete;
	HpUI(HpUI&& _Other) noexcept = delete;
	HpUI& operator=(const HpUI& _Other) = delete;
	HpUI& operator=(HpUI&& _Other) noexcept = delete;

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector;
	float StartHP;

	void Start() override;
};

