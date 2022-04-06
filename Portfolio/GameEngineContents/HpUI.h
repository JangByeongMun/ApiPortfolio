#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include <stack>
#include "ContentsEnum.h"

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

	void AddMaxHP(int _value, int _heal = 0);
	void SetCurrentHP(int _value);
	void ChangeCurrentHP(int _value);
	void AddColorHeart(HeartType _Type);

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	std::stack<int> AddHeart_;

	int MaxHP_;
	int CurrentHP_;

	void Start() override;
};

