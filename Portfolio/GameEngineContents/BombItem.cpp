#include "BombItem.h"
#include "Player.h"

BombItem::BombItem() 
	: Type_(BombType::None)
	, Renderer_(nullptr)
{
}

BombItem::~BombItem() 
{
}

void BombItem::SetType(BombType _Type)
{
	Renderer_ = CreateRenderer("pickup_016_bomb.bmp", RenderPivot::CENTER, { 0, 0 });

	Type_ = _Type;
	switch (Type_)
	{
	case BombType::None:
		Renderer_->SetIndex(2);
		break;
	case BombType::Normal:
		Renderer_->SetIndex(0);
		break;
	case BombType::Two:
		Renderer_->SetIndex(1);
		break;
	default:
		Renderer_->SetIndex(2);
		break;
	}

	Collision_ = CreateCollision("Item", { 60, 60 });
}

void BombItem::Update()
{
	/////// Ãæµ¹
	if (true == Collision_->IsUpdate() && true == Collision_->CollisionCheckRect("Player"))
	{
		switch (Type_)
		{
		case BombType::None:
			break;
		case BombType::Normal:
			Player::MainPlayer->AddItem(ItemType::Bomb);
			break;
		case BombType::Two:
			Player::MainPlayer->AddItem(ItemType::BombTwo);
			break;
		default:
			break;
		}

		Death();
	}
	
	SetObjectMove();
}

