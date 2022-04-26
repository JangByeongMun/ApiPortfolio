#include "Player.h"
#include "PassiveItem.h"
#include "PlayerHP.h"
#include "Poop.h"
#include "ActiveUI.h"

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
		GetLevel()->CreateActor<Poop>()->SetPosition(GetPosition());
		break;
	case ActiveType::Item045:
		GetPlayerHP()->AddRedHp(1, false);
		break;
	case ActiveType::Max:
		break;
	default:
		break;
	}

	SetGaze(0);
}

void Player::ChangeActiveGaze()
{

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
	case PassiveType::Default:
		break;
	case PassiveType::Item001:
		AttackSpeed_ += 0.7f;
		break;
	case PassiveType::Max:
		break;
	default:
		break;
	}
}
void Player::MakeItemRenderer(PassiveType _Type)
{
	switch (_Type)
	{
	case PassiveType::Default:
		break;
	case PassiveType::Item001:
		EffectItem1();
		break;
	case PassiveType::Max:
		break;
	default:
		break;
	}
}

void Player::EffectItem1()
{
	std::string Name = "costume_058_sadonion.bmp";
	GameEngineRenderer* chracterRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, -8 });
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