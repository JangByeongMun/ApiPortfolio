#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include "ContentsEnum.h"

class PlayerHP : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerHP();
	~PlayerHP();

	// delete Function
	PlayerHP(const PlayerHP& _Other) = delete;
	PlayerHP(PlayerHP&& _Other) noexcept = delete;
	PlayerHP& operator=(const PlayerHP& _Other) = delete;
	PlayerHP& operator=(PlayerHP&& _Other) noexcept = delete;

	void UpdateUI();
	void SetMaxHp(int _Value);
	void AddMaxHp(int _Value, int _Heal = -1);
	void AddRedHp(int _Value, bool _IsHalf = "false");
	void AddHearts(int _Value, HeartType _Type, bool _IsHalf = false);

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	std::vector<GameEngineRenderer*> ShadowRendererVector_;
	std::vector<HeartType> AddHeartVector_;

	const int MaxCount = 12;

	int MaxRedHP_;
	int CurrentRedHP_;
	int CurrentAddHP_;
	bool IsHalfRed_;
	bool IsHalfAdd_;

	void Start() override;
	void PlayerDeadCheck();
};

