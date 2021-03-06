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
	bool AddRedHp(bool _IsHalf = "false");
	bool AddHearts(HeartData _Type, bool _IsHalf = false);
	void MinusHearts(bool _IsHalf);

	inline bool IsFullRed()
	{
		return MaxRedHP_ <= CurrentRedHP_;
	}

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	std::vector<GameEngineRenderer*> ShadowRendererVector_;
	std::vector<HeartData> AddHeartVector_;

	const int MaxCount = 12;

	int MaxRedHP_;
	int CurrentRedHP_;
	int CurrentAddHP_;
	bool IsHalfRed_;
	bool IsHalfAdd_;
	bool IsDeath_;

	void Start() override;
	void PlayerDeadCheck();
};

