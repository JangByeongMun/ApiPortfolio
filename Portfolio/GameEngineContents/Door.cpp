#include "Door.h"
#include <string>
#include <GameEngine/GameEngineRenderer.h>

Door::Door() 
	: Type_()
	, Dir_()
{
}

Door::~Door() 
{
}

void Door::Setting(DoorType _Type, DoorDir _Dir)
{
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
		Name += "01_normaldoor";
		break;
	case DoorType::Boss:
		Name += "01_normaldoor";
		break;
	case DoorType::Max:
		Name += "01_normaldoor";
		break;
	default:
		break;
	}

	switch (Dir_)
	{
	case DoorDir::Up:
		Name += "_Up.bmp";
		break;
	case DoorDir::Down:
		Name += "_Down.bmp";
		break;
	case DoorDir::Left:
		Name += "_Left.bmp";
		break;
	case DoorDir::Right:
		Name += "_Right.bmp";
		break;
	default:
		break;
	}

	CreateRenderer(Name)->SetIndex(0);
}

