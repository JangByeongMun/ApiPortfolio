#include "BatteryItem.h"
#include "Player.h"

BatteryItem::BatteryItem() 
{
}

BatteryItem::~BatteryItem() 
{
}

void BatteryItem::Start()
{
	CreateRenderer("pickup_018_littlebattery.bmp", RenderPivot::CENTER, { 0, 0 });
	Collision_ = CreateCollision("Item", { 60, 60 });
}

void BatteryItem::Update()
{
	if (true == Player::MainPlayer->IsActiveOn())
	{
		return;
	}

	if (true == Collision_->IsUpdate() && true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->AddItem(ItemType::Battery);
		Death();
	}
}

