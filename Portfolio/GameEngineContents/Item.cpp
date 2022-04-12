#include "Item.h"

Item::Item() 
{
}

Item::Item(float4 _Scale)
{
	Collision_ = CreateCollision("Bomb", { 96, 96 }, { 0, 0 });
}

Item::~Item() 
{
}

void Item::Update()
{
	if (true == Collision_->CollisionCheck("PlayerHitBox", CollisionType::Rect, CollisionType::Rect))
	{
		AddToPlayer();
	}
}

void Item::AddToPlayer()
{
	
}

