#include "Item.h"
#include "Player.h"

Item::Item()
	: Collision_()
	, Type_(ItemType::None)
{
}

Item::Item(float4 _Scale)
	: Collision_()
	, Type_(ItemType::None)
{
}

Item::~Item() 
{
}

void Item::SetType(ItemType _Type)
{
	Type_ = _Type;

	int SelectInt = static_cast<int>(_Type);
	for (int i = 0; i < RendererVector_.size(); i++)
	{
		if (SelectInt == i)
		{
			RendererVector_[i]->On();
		}
		else
		{
			RendererVector_[i]->Off();
		}
	}
}

ItemType Item::GetType()
{
	return Type_;
}

void Item::Start()
{
	RendererVector_.push_back(CreateRenderer("trinket_001_swallowedpenny.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_002_petrifiedpoop.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_003_aaabattery.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_004_brokenremote.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_005_purpleheart.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_006_brokenmagnet.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_008_cartridge.bmp"));
	RendererVector_.push_back(CreateRenderer("trinket_009_pulseworm.bmp"));

	for (int i = 0; i < RendererVector_.size(); i++)
	{
		RendererVector_[i]->Off();
	}

	Collision_ = CreateCollision("Accessory", { 50, 50 }, { 0, 0 });
}

void Item::Update()
{
	if (ItemType::None == Type_)
	{
		return;
	}

	if (true == Collision_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
	{
		Player::MainPlayer->AddItem(Type_);
		Death();
	}
}