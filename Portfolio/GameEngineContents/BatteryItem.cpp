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
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		float4 TmpDir = GetPosition() - Player::MainPlayer->GetPosition();
		TmpDir.Normal2D();
		AddDir(TmpDir * 100.0f * GameEngineTime::GetDeltaTime());
	}
	SetObjectMove();

	if (true == Player::MainPlayer->IsActiveOn())
	{
		return;
	}

	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->AddItem(ItemType::Battery);
		Death();
	}
}

