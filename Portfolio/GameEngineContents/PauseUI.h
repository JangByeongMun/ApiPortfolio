#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

// Ό³Έν :
class PauseUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PauseUI();
	~PauseUI();

	// delete Function
	PauseUI(const PauseUI& _Other) = delete;
	PauseUI(PauseUI&& _Other) noexcept = delete;
	PauseUI& operator=(const PauseUI& _Other) = delete;
	PauseUI& operator=(PauseUI&& _Other) noexcept = delete;

	void TurnOn(bool _On);
	void SettingValue();

protected:

private:
	bool IsPause_;
	std::vector<GameEngineRenderer*> RendererVector_;
	std::vector<float4> ArrowPosVector_;
	GameEngineRenderer* ArrowRenderer_;
	int ArrowIndex_;

	void Start() override;
	void Update() override;
	void AddArrowIndex(int _Value);
	void Select(int _Index);
	
};

