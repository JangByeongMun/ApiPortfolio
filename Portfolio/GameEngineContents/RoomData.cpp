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

void RoomData::AddPassive(int _X, int _Y, PassiveType _Type)
{
	AllPassives_.push_back(PassiveData(_X, _Y, _Type));
}

void RoomData::AddBoss(int _X, int _Y, BossType _Type)
{
	AllBoss_.push_back(BossData(_X, _Y, _Type));
}
