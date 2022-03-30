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

void RoomData::Render()
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			Rectangle(
				GameEngineWindow::GetHDC(),
				StartX + (x * ScaleX),
				StartY + (y * ScaleY),
				StartX + ((x+1) * ScaleX),
				StartY + ((y+1) * ScaleY)
				);
		}
	}
}

bool RoomData::operator()(const MapPos& _Left, const MapPos& _Right)
{
	return _Left.n < _Right.n;
}