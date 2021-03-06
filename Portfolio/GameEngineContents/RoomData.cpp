#include "RoomData.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapPos.h"
#include "RoomActor.h"

RoomData::RoomData() 
	: RoomType_(RoomType::Default)
	, AllBlock_{}
	, AllMonster_{}
	, AllPassives_{}
	, AllBoss_{}
{
}

RoomData::RoomData(const RoomData& _Other)
	: RoomType_(RoomType::Default)
	, AllBlock_{}
	, AllMonster_{}
	, AllPassives_{}
	, AllBoss_{}
{
	RoomType_ = _Other.RoomType_;

	AllBlock_.clear();
	for (int i = 0; i < _Other.AllBlock_.size(); i++)
	{
		AllBlock_.push_back(_Other.AllBlock_[i]);
	}

	AllMonster_.clear();
	for (int i = 0; i < _Other.AllMonster_.size(); i++)
	{
		AllMonster_.push_back(_Other.AllMonster_[i]);
	}

	AllPassives_.clear();
	for (int i = 0; i < _Other.AllPassives_.size(); i++)
	{
		AllPassives_.push_back(_Other.AllPassives_[i]);
	}

	AllBoss_.clear();
	for (int i = 0; i < _Other.AllBoss_.size(); i++)
	{
		AllBoss_.push_back(_Other.AllBoss_[i]);
	}

	AllShop_.clear();
	for (int i = 0; i < _Other.AllShop_.size(); i++)
	{
		AllShop_.push_back(_Other.AllShop_[i]);
	}

	AllPickUp_.clear();
	for (int i = 0; i < _Other.AllPickUp_.size(); i++)
	{
		AllPickUp_.push_back(_Other.AllPickUp_[i]);
	}
}

RoomData::~RoomData() 
{
}

RoomData& RoomData::operator=(RoomData& _Other)
{
	RoomType_ = _Other.RoomType_;

	AllBlock_.clear();
	for (int i = 0; i < _Other.AllBlock_.size(); i++)
	{
		AllBlock_.push_back(_Other.AllBlock_[i]);
	}

	AllMonster_.clear();
	for (int i = 0; i < _Other.AllMonster_.size(); i++)
	{
		AllMonster_.push_back(_Other.AllMonster_[i]);
	}

	AllPassives_.clear();
	for (int i = 0; i < _Other.AllPassives_.size(); i++)
	{
		AllPassives_.push_back(_Other.AllPassives_[i]);
	}

	AllBoss_.clear();
	for (int i = 0; i < _Other.AllBoss_.size(); i++)
	{
		AllBoss_.push_back(_Other.AllBoss_[i]);
	}

	AllShop_.clear();
	for (int i = 0; i < _Other.AllShop_.size(); i++)
	{
		AllShop_.push_back(_Other.AllShop_[i]);
	}

	AllPickUp_.clear();
	for (int i = 0; i < _Other.AllPickUp_.size(); i++)
	{
		AllPickUp_.push_back(_Other.AllPickUp_[i]);
	}

	return *this;
}

void RoomData::AddBlock(int _X, int _Y, BlockType _Type)
{
	AllBlock_.push_back(BlockData(_X, _Y, _Type));
}

void RoomData::AddMonster(int _X, int _Y, MonsterType _Type)
{
	AllMonster_.push_back(MonsterData(_X, _Y, _Type));
}

void RoomData::AddPassive(int _X, int _Y)
{
	AllPassives_.push_back(PassiveData(_X, _Y));
}

void RoomData::AddBoss(int _X, int _Y, BossType _Type)
{
	AllBoss_.push_back(BossData(_X, _Y, _Type));
}

void RoomData::AddShop(int _X, int _Y, ShopType _Type)
{
	AllShop_.push_back(ShopData(_X, _Y, _Type));
}

void RoomData::AddPickup(int _X, int _Y, ItemType _Type)
{
	AllPickUp_.push_back(PickupData(_X, _Y, _Type));
}