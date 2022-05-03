#include "PassiveItem.h"
#include <GameEngineBase/GameEngineTime.h>
#include "Player.h"

std::vector<std::string> PassiveItem::ItemNameVector_ = {};


PassiveItem::PassiveItem()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, Type_(PassiveType::Default)
	, AnimTimer_(0.0f)
{
}

PassiveItem::~PassiveItem() 
{
}

void PassiveItem::Setting(PassiveType _Type)
{
	Type_ = _Type;

	{
	 	GameEngineRenderer* Renderer = CreateRenderer("levelitem_001_itemaltar.bmp", static_cast<int>(ORDER::PLAYER));
		Renderer->SetPivot({0, 20});
	}

	Renderer_ = CreateRenderer(ItemNameVector_[static_cast<int>(Type_)], static_cast<int>(ORDER::PLAYER));
	Collision_ = CreateCollision("Passive", { 50, 50 });
}

void PassiveItem::Start()
{
	ItemNameVector_.push_back("None.bmp");
	ItemNameVector_.push_back("collectibles_001_thesadonion.bmp");
	ItemNameVector_.push_back("collectibles_004_cricketshead.bmp");
	ItemNameVector_.push_back("collectibles_007_bloodofthemartyr.bmp");
	ItemNameVector_.push_back("collectibles_012_magicmushroom.bmp");
	ItemNameVector_.push_back("collectibles_015_heart.bmp");
	ItemNameVector_.push_back("collectibles_017_skeletonkey.bmp");
	ItemNameVector_.push_back("collectibles_019_boom.bmp");
	ItemNameVector_.push_back("collectibles_022_lunch.bmp");
	ItemNameVector_.push_back("collectibles_023_dinner.bmp");
	ItemNameVector_.push_back("collectibles_027_woodenspoon.bmp");
	ItemNameVector_.push_back("collectibles_031_momslipstick.bmp");
	ItemNameVector_.push_back("collectibles_072_rosary.bmp");
	ItemNameVector_.push_back("collectibles_109_moneyispower.bmp");
	ItemNameVector_.push_back("collectibles_121_oddmushroomlarge.bmp");
	ItemNameVector_.push_back("collectibles_226_blacklotus.bmp");
	ItemNameVector_.push_back("collectibles_121_oddmushroomlarge.bmp");
	ItemNameVector_.push_back("collectibles_245_2020.bmp");
	ItemNameVector_.push_back("collectibles_246_bluemap.bmp");
	ItemNameVector_.push_back("collectibles_302_leo.bmp");
	ItemNameVector_.push_back("collectibles_307_capricorn.bmp");
}

void PassiveItem::Update()
{
	// 플레이어와 충돌
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->AddPassive(Type_);
		Death();
	}

	// 애니메이션 
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ <= 0.5f)
	{
		float4 LerpFloat4 = float4::Lerp({ 0, -35 }, { 0, -45 }, AnimTimer_ * 2);
		Renderer_->SetPivot(LerpFloat4);
	}
	else if (AnimTimer_ <= 1.0f)
	{
		float4 LerpFloat4 = float4::Lerp({ 0, -45 }, {0, -35}, (AnimTimer_-0.5f) * 2);
		Renderer_->SetPivot(LerpFloat4);
	}
	else
	{
		AnimTimer_ = 0.0f;
	}
}

