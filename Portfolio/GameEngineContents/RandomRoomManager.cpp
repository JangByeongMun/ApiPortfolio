#include "RandomRoomManager.h"
#include "RoomData.h"

RandomRoomManager* RandomRoomManager::inst_ = new RandomRoomManager();

bool RandomRoomManager::ChangeFloor(const int& _floor)
{
	currentFloor_ = _floor;
	switch (currentFloor_)
	{
	case 1:
		currentMapCount_ = 9;
		break;
	case 2:
		currentMapCount_ = 12;
		break;
	case 3:
		currentMapCount_ = 15;
		break;
	default:
		return false;
	}

	// 일단 새로만든 룸데이터를 만들고 여기에 값을 복사하도록 깊은복사를 만드는식으로?
	RoomData* newRoomData = new RoomData();
	//currentMaps_.insert(make_pair(float4(6, 6), newRoomData));

	return true;
}

RandomRoomManager::RandomRoomManager()
	: currentFloor_(0)
	, currentMapCount_(0)
{
}

RandomRoomManager::~RandomRoomManager()
{
	map<int, vector<RoomData*>>::iterator beginIter = allMaps_.begin();
	map<int, vector<RoomData*>>::iterator endIter = allMaps_.end();
	for (; beginIter != endIter; ++beginIter)
	{
		vector<RoomData*>& tmpGroup = beginIter->second;
		
		vector<RoomData*>::iterator beginVectorIter = tmpGroup.begin();
		vector<RoomData*>::iterator endVectorIter = tmpGroup.end();
		for (; beginVectorIter != endVectorIter; ++beginVectorIter)
		{
			if (nullptr == (*beginVectorIter))
			{
				continue;
			}
	
			delete (*beginVectorIter);
			(*beginVectorIter) = nullptr;
		}
	}
}

