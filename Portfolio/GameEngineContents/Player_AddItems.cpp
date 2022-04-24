#include "Player.h"

void Player::MakeItemRenderer(PassiveType _Type)
{
	switch (_Type)
	{
	case PassiveType::Default:
		break;
	case PassiveType::Item1:
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