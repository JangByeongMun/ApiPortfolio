#include "PlayerUI.h"
#include "Player.h"
#include "PlayerHP.h"
#include "CardUI.h"
#include "ItemUI.h"
#include "AccessoryUI.h"
#include "MiniMap.h"

PlayerUI::PlayerUI() 
	: PlayerHP_(nullptr)
	, CardUI_(nullptr)
	, ItemUI_(nullptr)
	, AccessoryUI_(nullptr)
	, MiniMap_(nullptr)
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
	MiniMap_ = GetLevel()->CreateActor<MiniMap>(static_cast<int>(ORDER::UI));
}

void PlayerUI::Setting()
{
	SetPlayerHP();
	SetItemUI();
	SetAccessoryUI();
	SetMiniMap();
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

void PlayerUI::UpdateMiniMap(float4 _Dir)
{
	MiniMap_->ChangeMap(_Dir);
}

void PlayerUI::DebugMiniMap()
{
	MiniMap_->SeeAllMap();
}

