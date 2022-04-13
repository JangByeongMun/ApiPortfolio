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

	void Setting();

	void SetMaxHP(int _Value);
	void AddMaxHP(int _Value, int _Heal = 0);
	void SetCurrentHP(int _Value);
	void AddCurrentHP(int _Value);
	void AddColorHeart(HeartType _Type);

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	std::stack<int> AddHeart_;

	int MaxHP_;
	int CurrentHP_;

	void Start() override;
};

