#include "RoomData.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapPos.h"

RoomData::RoomData() 
	:AllBlock_{}
{
}

RoomData::~RoomData() 
{
}

bool RoomData::operator()(const MapPos& _Left, const MapPos& _Right)
{
	return _Left.n < _Right.n;
}

void RoomData::AddBlock(int _X, int _Y, TileType _Type)
{
	AllBlock_.push_back(Tile(_X, _Y, _Type));
}
