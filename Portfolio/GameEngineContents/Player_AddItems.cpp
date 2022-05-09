#include "Player.h"
#include "PassiveItem.h"
#include "PlayerHP.h"
#include "Poop.h"
#include "ActiveUI.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"
#include "PlayerUI.h"
#include "MiniMap.h"

void Player::SetGaze(int _Value)
{
	CurrentGaze_ = _Value;
	if (CurrentGaze_ <= 0)
	{
		CurrentGaze_ = 0;
	}
	if (CurrentGaze_ >= MaxGaze_)
	{
		CurrentGaze_ = MaxGaze_;
	}
	GetActiveUI()->SetGaze(CurrentGaze_);
}

void Player::AddGaze(int _Value)
{
	CurrentGaze_ += _Value;

	if (CurrentGaze_ >= MaxGaze_)
	{
		CurrentGaze_ = MaxGaze_;
	}
	GetActiveUI()->SetGaze(CurrentGaze_);
}

void Player::UseActive()
{
	if (false == IsActiveOn())
	{
		return;
	}

	switch (ActiveType_)
	{
	case ActiveType::Default:
		break;
	case ActiveType::Item034:
		IsUsingActive = true;
		Damage_ += 2;
		break;
	case ActiveType::Item036:
		GetLevel()->CreateActor<Poop>()->SetPosition(GetPosition() + float4(0, -60));
		{
			std::string TmpName = "fart";
			TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(0, 3)) + ".wav";
			GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 0.1f * Option_SFX);
		}
		break;
	case ActiveType::Item045:
		GetPlayerHP()->AddRedHp(false);
		GameEngineSound::SoundPlayOneShotWithVolume("vamp.wav", 0, 0.1f * Option_SFX);
		break;
	case ActiveType::Max:
		break;
	default:
		break;
	}

	SetGaze(0);
}

void Player::AddPassive(PassiveType _Type)
{
	std::string TmpName = PassiveItem::ItemNameVector_[static_cast<int>(_Type)];

	AddPassiveEffect(_Type);
	MakeItemRenderer(_Type);

	PassiveVector_.push_back(_Type);
	ChangeBodyState(PlayerBodyState::Acheive);
	ChangeHeadState(PlayerHeadState::Acheive);
	SetAcheiveRenderer(TmpName);
}
void Player::AddPassiveEffect(PassiveType _Type)
{
	switch (_Type)
	{
	case PassiveType::Item001:
		AttackSpeed_ += 0.7f;
		break;
	case PassiveType::Item004:
		Damage_ += 1.0f;
		break;
	case PassiveType::Item007:
		Damage_ += 1.2f;
		break;
	case PassiveType::Item012:
		GetPlayerHP()->AddMaxHp(1);
		MoveSpeed_ += 0.4f;
		Damage_ += 0.5f;
		Range_ += 1.5f;
		break;
	case PassiveType::Item015:
		GetPlayerHP()->AddMaxHp(1, 12);
		break;
	case PassiveType::Item017:
		for (int i = 0; i < 60; i++)
		{
			AddItem(ItemType::KeyTwo);
		}
		break;
	case PassiveType::Item019:
		for (int i = 0; i < 5; i++)
		{
			AddItem(ItemType::BombTwo);
		}
		break;
	case PassiveType::Item022:
		GetPlayerHP()->AddMaxHp(1, 1);
		break;
	case PassiveType::Item023:
		GetPlayerHP()->AddMaxHp(1, 1);
		break;
	case PassiveType::Item027:
		MoveSpeed_ += 0.4f;
		break;
	case PassiveType::Item031:
		Range_ += 2.5f;
		break;
	case PassiveType::Item072:
		GetPlayerHP()->AddHearts(HeartData::SoulHeart, false);
		GetPlayerHP()->AddHearts(HeartData::SoulHeart, false);
		GetPlayerHP()->AddHearts(HeartData::SoulHeart, false);
		AttackSpeed_ += 0.5f;
		break;
	case PassiveType::Item109:
		Have109_ = true;
		AddItem(ItemType::MoneySilver);
		break;
	case PassiveType::Item121:
		GetPlayerHP()->AddMaxHp(1, 0);
		Damage_ += 0.4f;
		Range_ += 0.25f;
		MoveSpeed_ -= 0.1f;
		break;
	case PassiveType::Item226:
		GetPlayerHP()->AddMaxHp(1, 1);
		GetPlayerHP()->AddHearts(HeartData::SoulHeart, false);
		GetPlayerHP()->AddHearts(HeartData::BlackHeart, false);
		break;
	case PassiveType::Item245:
		Have245_ = true;
		break;
	case PassiveType::Item246:
		Have246_ = true;
		PlayerUI_->MiniMap_->SeeSpecialRooms();
		break;
	case PassiveType::Item302:
		Have302_ = true;
		break;
	case PassiveType::Item307:
		AddItem(ItemType::Money);
		AddItem(ItemType::Key);
		AddItem(ItemType::Bomb);
		GetPlayerHP()->AddMaxHp(1);
		Damage_ += 0.6f;
		MoveSpeed_ += 0.5f;
		Range_ += 1.5f;
		AttackSpeed_ += 1.0f;
		break;
	default:
		break;
	}
}
void Player::MakeItemRenderer(PassiveType _Type)
{
	switch (_Type)
	{
	case PassiveType::Item001:
		EffectItem001();
		break;
	case PassiveType::Item015:
		EffectItem015();
		break;
	case PassiveType::Item072:
		EffectItem072();
		break;

	case PassiveType::Item007:
	case PassiveType::Item017:
	case PassiveType::Item019:
	case PassiveType::Item027:
	case PassiveType::Item031:
	case PassiveType::Item109:
	case PassiveType::Item226:
	case PassiveType::Item245:
	case PassiveType::Item302:
	case PassiveType::Item307:
		EffectItemDefault(_Type);
		break;

	default:
		break;
	}
}

bool Player::IsAlreadyHave(PassiveType _Type)
{
	for (int i = 0; i < PassiveVector_.size(); i++)
	{
		if (PassiveVector_[i] == _Type)
		{
			return true;
		}
	}
	return false;
}

void Player::EffectItem001()
{
	std::string Name = "costume_001_sadonion.bmp";
	GameEngineRenderer* chracterRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, -8 }, static_cast<int>(ORDER::FRONTPLAYER));
	chracterRenderer_->CreateAnimation(Name, "Idle", 0, 2, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Left_1", 6, 8, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Left_2", 6, 8, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Right_1", 3, 5, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Right_2", 3, 5, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Up_1", 0, 2, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Up_2", 0, 2, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Down_1", 0, 2, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Down_2", 0, 2, 0.1f, true);
	chracterRenderer_->ChangeAnimation("Idle");
	HeadAddRender_.push_back(chracterRenderer_);
}

void Player::EffectItem015()
{
	std::string Name = "costume_015_heart.bmp";
	GameEngineRenderer* chracterRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, 35 }, static_cast<int>(ORDER::FRONTPLAYER));
	chracterRenderer_->CreateAnimation(Name, "Idle", 0, 2, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Left_1", 12, 14, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Left_2", 12, 14, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Right_1", 5, 7, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Right_2", 5, 7, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Up_1", 8, 9, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Up_2", 8, 9, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Down_1", 0, 2, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Down_2", 0, 2, 0.1f, true);
	chracterRenderer_->ChangeAnimation("Idle");
	HeadAddRender_.push_back(chracterRenderer_);
}

void Player::EffectItem072()
{
	std::string Name = "costume_072_rosary.bmp";
	GameEngineRenderer* chracterRenderer_ = CreateRenderer(RenderPivot::CENTER, { -10, 20 }, static_cast<int>(ORDER::FRONTPLAYER));
	chracterRenderer_->CreateAnimation(Name, "Idle", 0, 1, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Left_1", 23, 23, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Left_2", 23, 23, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Right_1", 18, 18, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Right_2", 18, 18, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Up_1", 10, 11, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Up_2", 10, 11, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Down_1", 0, 1, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Down_2", 0, 1, 0.1f, true);
	chracterRenderer_->ChangeAnimation("Idle");
	HeadAddRender_.push_back(chracterRenderer_);
}

void Player::EffectItemDefault(PassiveType _Type)
{
	std::string Name = "";
	float4 TmpPos = { 0, -8 };
	switch (_Type)
	{
	case PassiveType::Item007:
		Name = "costume_007_bloodofthemartyr.bmp";
		break;
	case PassiveType::Item017:
		Name = "costume_017_skeletonkey_white.bmp";
		break;
	case PassiveType::Item019:
		Name = "costume_019_boom.bmp";
		break;
	case PassiveType::Item027:
		Name = "costume_027_woodenspoon.bmp";
		break;
	case PassiveType::Item031:
		Name = "costume_031_momslipstick.bmp";
		break;
	case PassiveType::Item109:
		Name = "costume_109_moneyispower.bmp";
		break;
	case PassiveType::Item226:
		Name = "costume_226_blacklotus.bmp";
		break;
	case PassiveType::Item245:
		Name = "costume_245_2020.bmp";
		break;
	case PassiveType::Item302:
		Name = "costume_302_leo.bmp";
		TmpPos = { 0, -15 };
		break;
	case PassiveType::Item307:
		Name = "costume_307_capricorn.bmp";
		TmpPos = { 0, -15 };
		break;
	default:
		break;
	}
	GameEngineRenderer* chracterRenderer_ = CreateRenderer(RenderPivot::CENTER, TmpPos, static_cast<int>(ORDER::FRONTPLAYER));
	chracterRenderer_->CreateAnimation(Name, "Idle", 0, 0, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Up_1", 4, 4, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Up_2", 4, 5, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Down_1", 0, 0, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Down_2", 0, 1, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Left_1", 6, 6, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Left_2", 6, 7, 0.1f, true);
	chracterRenderer_->CreateAnimation(Name, "Right_1", 2, 2, 0.1f, false);
	chracterRenderer_->CreateAnimation(Name, "Right_2", 2, 3, 0.1f, true);
	chracterRenderer_->ChangeAnimation("Idle");
	HeadAddRender_.push_back(chracterRenderer_);
}