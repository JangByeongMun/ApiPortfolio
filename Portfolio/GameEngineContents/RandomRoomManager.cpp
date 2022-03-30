#include "RandomRoomManager.h"
#include "RoomData.h"

RandomRoomManager* RandomRoomManager::Inst_ = new RandomRoomManager();

bool RandomRoomManager::ChangeFloor(const int& _Floor)
{
	currentFloor_ = _Floor;
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
	RoomData* NewRoomData = new RoomData();
	CurrentMaps_.insert(make_pair(MapPos(), NewRoomData));

	return true;
}

RandomRoomManager::RandomRoomManager()
	: currentFloor_(0)
	, currentMapCount_(0)
{
}

RandomRoomManager::~RandomRoomManager()
{
	map<int, vector<RoomData*>>::iterator BeginIter = AllMaps_.begin();
	map<int, vector<RoomData*>>::iterator EndIter = AllMaps_.end();
	for (; BeginIter != EndIter; ++BeginIter)
	{
		vector<RoomData*>& TmpGroup = BeginIter->second;
		
		vector<RoomData*>::iterator BeginVectorIter = TmpGroup.begin();
		vector<RoomData*>::iterator EndVectorIter = TmpGroup.end();
		for (; BeginVectorIter != EndVectorIter; ++BeginVectorIter)
		{
			if (nullptr == (*BeginVectorIter))
			{
				continue;
			}
	
			delete (*BeginVectorIter);
			(*BeginVectorIter) = nullptr;
		}
	}
}

