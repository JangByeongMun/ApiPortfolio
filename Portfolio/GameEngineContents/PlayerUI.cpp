#include "PlayerUI.h"
#include "Player.h"
#include "PlayerHP.h"
#include "CardUI.h"
#include "ItemUI.h"
#include "AccessoryUI.h"
#include "MiniMap.h"
#include "PlayLevel.h"
#include <GameEngine/GameEngine.h>
#include "ActiveUI.h"
#include "PauseUI.h"

PlayerUI::PlayerUI() 
	: PlayerHP_(nullptr)
	, CardUI_(nullptr)
	, ItemUI_(nullptr)
	, AccessoryUI_(nullptr)
	, MiniMap_(nullptr)
	, ActiveUI_(nullptr)
	, PauseUI_(nullptr)
{
}

PlayerUI::~PlayerUI() 
{
}

void PlayerUI::Start()
{
	PlayerHP_ = GetLevel()->CreateActor<PlayerHP>(static_cast<int>(ORDER::UI));
	CardUI_ = GetLevel()->CreateActor<CardUI>(static_cast<int>(ORDER::UI));
	ItemUI_ = GetLevel()->CreateActor<ItemUI>(static_cast<int>(ORDER::UI));
	AccessoryUI_ = GetLevel()->CreateActor<AccessoryUI>(static_cast<int>(ORDER::UI));
	ActiveUI_ = GetLevel()->CreateActor<ActiveUI>((int)ORDER::UI);
	PauseUI_ = GetLevel()->CreateActor<PauseUI>((int)ORDER::FRONTUI);
}

void PlayerUI::Setting()
{
	SetPlayerHP();
	SetItemUI();
	SetAccessoryUI();
	SetActiveUI();
	SetPauseUI();
}

void PlayerUI::LevelChangeStart(GameEngineLevel* _BeforeLevel)
{
	if (nullptr == dynamic_cast<PlayLevel*>(GetLevel()))
	{
		PlayerHP_->Off();
		CardUI_->Off();
		ItemUI_->Off();
		AccessoryUI_->Off();
		ActiveUI_->Off();
		PauseUI_->Off();
	}
	else
	{
		PlayerHP_->On();
		CardUI_->On();
		ItemUI_->On();
		AccessoryUI_->On();
		ActiveUI_->On();
		PauseUI_->Off();
	}
}

void PlayerUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (
		_NextLevel == GameEngine::GetInst().FindLevel("Ending") ||
		_NextLevel == GameEngine::GetInst().FindLevel("Menu") ||
		_NextLevel == GameEngine::GetInst().FindLevel("Title")
		)
	{
		PlayerHP_->NextLevelOff();
		CardUI_->NextLevelOff();
		ItemUI_->NextLevelOff();
		AccessoryUI_->NextLevelOff();
		ActiveUI_->NextLevelOff();
		PauseUI_->NextLevelOff();
	}
	else
	{
		PlayerHP_->NextLevelOn();
		CardUI_->NextLevelOn();
		ItemUI_->NextLevelOn();
		AccessoryUI_->NextLevelOn();
		ActiveUI_->NextLevelOn();
		PauseUI_->NextLevelOn();
	}
}

void PlayerUI::SetPlayerHP()
{
	PlayerHP_->SetMaxHp(Player::MainPlayer->MaxHp_);
}

void PlayerUI::SetCardUI()
{
}

void PlayerUI::SetItemUI()
{
	ItemUI_->Reset();
	ItemUI_->SetMoney(Player::MainPlayer->MoneyCount_);
	ItemUI_->SetBomb(Player::MainPlayer->BombCount_);
	ItemUI_->SetKey(Player::MainPlayer->KeyCount_, Player::MainPlayer->IsMasterKey_);
}

void PlayerUI::SetAccessoryUI()
{
	AccessoryUI_->SetAccessory(Player::MainPlayer->HavingAccessory_);
}

void PlayerUI::SetMiniMap()
{
	MiniMap_->MakeNode();
	MiniMap_->ChangeMap({0, 0});
}

void PlayerUI::SetActiveUI()
{
	ActiveUI_->SettingUI();
}

void PlayerUI::SetPauseUI()
{
	PauseUI_->SettingValue();
}

void PlayerUI::MakeMiniMap()
{
	MiniMap_ = GetLevel()->CreateActor<MiniMap>(static_cast<int>(ORDER::UI));
	SetMiniMap();
}

void PlayerUI::UpdateMiniMap(float4 _Dir)
{
	MiniMap_->ChangeMap(_Dir);
}

void PlayerUI::DebugMiniMap()
{
	MiniMap_->SeeAllMap();
}

