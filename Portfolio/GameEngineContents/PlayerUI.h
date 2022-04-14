#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>

// 설명 : 플레이어가 관련한 ui들 전체 관리용 클래스
class Player;
class HPUI;
class CardUI;
class HavingItemUI;
class ItemUI;
class PlayerUI : public GameEngineActor
{
	friend GameEngineLevel;
	friend Player;
private:
	PlayerUI();
	~PlayerUI();

	PlayerUI(const PlayerUI& _Other) = delete;
	PlayerUI(PlayerUI&& _Other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI& _Other) = delete;
	PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;

private:
	HPUI* HpUI_;
	CardUI* CardUI_;
	HavingItemUI* HavingItemUI_;
	ItemUI* ItemUI_;

	void Start() override;
	void Setting();
};

