#include "PlayerUI.h"
#include "Player.h"
#include "HPUI.h"
#include "CardUI.h"
#include "ItemUI.h"
#include "AccessoryUI.h"

PlayerUI::PlayerUI() 
	: HpUI_(nullptr)
	, CardUI_(nullptr)
	, ItemUI_(nullptr)
{
}

PlayerUI::~PlayerUI() 
{
}

void PlayerUI::Start()
{
	HpUI_ = GetLevel()->CreateActor<HPUI>(static_cast<int>(ORDER::UI));
	CardUI_ = GetLevel()->CreateActor<CardUI>(static_cast<int>(ORDER::UI));
	ItemUI_ = GetLevel()->CreateActor<ItemUI>(static_cast<int>(ORDER::UI));
	AccessoryUI_ = GetLevel()->CreateActor<AccessoryUI>(static_cast<int>(ORDER::UI));
}

void PlayerUI::Setting()
{
	SetHpUI();
	SetItemUI();
	SetAccessoryUI();
}

void PlayerUI::SetHpUI()
{
	HpUI_->AddMaxHp(Player::MainPlayer->MaxHp_);
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

