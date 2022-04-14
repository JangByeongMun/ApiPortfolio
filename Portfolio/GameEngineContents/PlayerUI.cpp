#include "PlayerUI.h"
#include "Player.h"
#include "HPUI.h"
#include "CardUI.h"
#include "HavingItemUI.h"
#include "ItemUI.h"

PlayerUI::PlayerUI() 
	: HpUI_(nullptr)
	, CardUI_(nullptr)
	, HavingItemUI_(nullptr)
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
	HavingItemUI_ = GetLevel()->CreateActor<HavingItemUI>(static_cast<int>(ORDER::UI));
	ItemUI_ = GetLevel()->CreateActor<ItemUI>(static_cast<int>(ORDER::UI));
}

void PlayerUI::Setting()
{
	ItemUI_->Reset();
	ItemUI_->SetMoney(Player::MainPlayer->MoneyCount_);
	ItemUI_->SetBomb(Player::MainPlayer->BombCount_);
	ItemUI_->SetKey(Player::MainPlayer->KeyCount_);
}

