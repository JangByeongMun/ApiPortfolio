#include "RoomData.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapPos.h"
#include "RoomActor.h"

RoomData::RoomData() 
	:AllBlock_{}
{
}

RoomData::RoomData(const RoomData& _Other)
{
	AllBlock_.clear();
	for (int i = 0; i < _Other.AllBlock_.size(); i++)
	{
		AllBlock_.push_back(_Other.AllBlock_[i]);
	}
}

RoomData::~RoomData() 
{
}

RoomData& RoomData::operator=(RoomData& _Other)
{
	AllBlock_.clear();
	for (int i = 0; i < _Other.AllBlock_.size(); i++)
	{
		AllBlock_.push_back(_Other.AllBlock_[i]);
	}

	return *this;
}

bool RoomData::operator()(const MapPos& _Left, const MapPos& _Right)
{
	return _Left.n < _Right.n;
}

void RoomData::AddBlock(int _X, int _Y, BlockData _Type)
{
	AllBlock_.push_back(Tile(_X, _Y, _Type));
}
