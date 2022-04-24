#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>

// 설명 : 플레이어가 관련한 ui들 전체 관리용 클래스
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

	void LevelChangeStart(GameEngineLevel* _BeforeLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

public:
	void SetPlayerHP();
	void SetCardUI();
	void SetItemUI();
	void SetAccessoryUI();
	void SetMiniMap();

	void MakeMiniMap();
	void UpdateMiniMap(float4 _Dir);
	void DebugMiniMap();

	inline PlayerHP* GetPlayerHP()
	{
		return PlayerHP_;
	}
};