#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include "ContentsEnum.h"

class HPUI : public GameEngineActor
{
public:
	// constrcuter destructer
	HPUI();
	~HPUI();

	// delete Function
	HPUI(const HPUI& _Other) = delete;
	HPUI(HPUI&& _Other) noexcept = delete;
	HPUI& operator=(const HPUI& _Other) = delete;
	HPUI& operator=(HPUI&& _Other) noexcept = delete;

	void UpdateUI();
	void AddMaxHp(int _Value, int _Heal);
	void AddRedHp(int _Value);
	void AddHearts(int _Value, HeartType _Type);

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	std::vector<HeartType> AddHeartVector_;

	const int MaxCount = 12;

	int MaxRedHP_;
	int CurrentRedHP_;
	int CurrentAddHP_;

	void Start() override;
};

