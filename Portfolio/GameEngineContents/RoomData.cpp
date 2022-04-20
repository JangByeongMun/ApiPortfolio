#include "RoomData.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapPos.h"
#include "RoomActor.h"

RoomData::RoomData() 
	: RoomType_(RoomType::Default)
	, AllBlock_{}
	, AllMonster_{}
{
}

RoomData::RoomData(const RoomData& _Other)
	: RoomType_(RoomType::Default)
	, AllBlock_{}
	, AllMonster_{}
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
