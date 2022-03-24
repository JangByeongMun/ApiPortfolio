#include "RoomData.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapPos.h"

RoomData::RoomData() 
	:allBlock_{}
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
				startX + (x * scaleX),
				startY + (y * scaleY),
				startX + ((x+1) * scaleX),
				startY + ((y+1) * scaleY)
				);
		}
	}
}

bool RoomData::operator()(const MapPos& _left, const MapPos& _right)
{
	return _left.n < _right.n;
}