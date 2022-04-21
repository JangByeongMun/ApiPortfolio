#include "Door.h"
#include <string>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"

Door::Door() 
	: Collision_(nullptr)
	, Type_()
	, Dir_()
{
}

Door::~Door() 
{
}

void Door::Setting(DoorType _Type, DoorDir _Dir)
{
	Collision_ = CreateCollision("Door", { 30, 30 });

	std::string Name = "door_";
	Type_ = _Type;
	Dir_ = _Dir;

	switch (Type_)
	{
	case DoorType::Default:
		Name += "01_normaldoor";
		break;
	case DoorType::Treasure:
		//Name += "02_treasureroomdoor";
		Name += "02_treasureroomdoor";
		break;
	case DoorType::Boss:
		Name += "10_bossroomdoor";
		break;
	case DoorType::Max:
		break;
	default:
		break;
	}

	switch (Dir_)
	{
	case DoorDir::Up:
		Collision_->SetPivot({0, -40});
		Name += "_Up.bmp";
		break;
	case DoorDir::Down:
		Collision_->SetPivot({ 0, 5 });
		Name += "_Down.bmp";
		break;
	case DoorDir::Left:
		Collision_->SetPivot({ -20, 0 });
		Name += "_Left.bmp";
		break;
	case DoorDir::Right:
		Collision_->SetPivot({ 20, 0 });
		Name += "_Right.bmp";
		break;
	default:
		break;
	}

	CreateRenderer(Name)->SetIndex(0);
}

void Door::Update()
{
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->ChangeRoom(Dir_);
	}
}

