#include "KeyItem.h"
#include "Player.h"

KeyItem::KeyItem() 
{
}

KeyItem::~KeyItem() 
{
}

void KeyItem::SetType(KeyType _Type)
{
	Renderer_ = CreateRenderer("pickup_003_key.bmp", RenderPivot::CENTER, {0, 0});

	Type_ = _Type;
	switch (Type_)
	{
	case KeyType::None:
		Renderer_->SetIndex(3);
		break;
	case KeyType::Normal:
		Renderer_->SetIndex(0);
		break;
	case KeyType::Two:
		Renderer_->SetIndex(2);
		break;
	case KeyType::Master:
		Renderer_->SetIndex(1);
		break;
	default:
		break;
	}

	Collision_ = CreateCollision("Item", {60, 60});
}

void KeyItem::Update()
{
	/////// Ãæµ¹
	if (true == Collision_->IsUpdate() && true == Collision_->CollisionCheckRect("Player"))
	{
		switch (Type_)
		{
		case KeyType::None:
			break;
		case KeyType::Normal:
			Player::MainPlayer->AddItem(ItemType::Key);
			break;
		case KeyType::Two:
			Player::MainPlayer->AddItem(ItemType::KeyTwo);
			break;
		case KeyType::Master:
			Player::MainPlayer->AddItem(ItemType::keyMaster);
			break;
		default:
			break;
		}

		Death();
	}

	SetObjectMove();
}