#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>

// ���� : �÷��̾ ������ ui�� ��ü ������ Ŭ����
class Player;
class PlayerHP;
class CardUI;
class ItemUI;
class AccessoryUI;
class MiniMap;
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
	PlayerHP* PlayerHP_;
	CardUI* CardUI_;
	ItemUI* ItemUI_;
	AccessoryUI* AccessoryUI_;
	MiniMap* MiniMap_;

	void Start() override;
	void Setting();

	void SetPlayerHP();
	void SetCardUI();
	void SetItemUI();
	void SetAccessoryUI();
	void SetMiniMap();


public: 
	inline PlayerHP* GetPlayerHP()
	{
		return PlayerHP_;
	}
};

