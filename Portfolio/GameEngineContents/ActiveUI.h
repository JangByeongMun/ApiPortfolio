#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsEnum.h"

// Ό³Έν :
class ActiveUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ActiveUI();
	~ActiveUI();

	// delete Function
	ActiveUI(const ActiveUI& _Other) = delete;
	ActiveUI(ActiveUI&& _Other) noexcept = delete;
	ActiveUI& operator=(const ActiveUI& _Other) = delete;
	ActiveUI& operator=(ActiveUI&& _Other) noexcept = delete;

	void SettingUI();

protected:

private:
	std::vector<GameEngineRenderer*> ItemRenderer;
	std::vector<GameEngineRenderer*> GazeRenderer;

	void Start() override;
	void SelectItemRenderer(int _Value);
	void SelectGazeRenderer(int _Value);
};

