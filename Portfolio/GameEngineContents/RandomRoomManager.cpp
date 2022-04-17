#include "RandomRoomManager.h"
#include "RoomData.h"

RandomRoomManager* RandomRoomManager::Inst_ = nullptr;
int StartX = 220;
int StartY = 135;
int ScaleX = 70;
int ScaleY = 75;

bool RandomRoomManager::ChangeFloor(const int& _Floor)
{
	CurrentFloor_ = _Floor;
	switch (CurrentFloor_)
	{
	case 1:
		CurrentMapCount_ = 9;
		break;
	case 2:
		CurrentMapCount_ = 12;
		break;
	case 3:
		CurrentMapCount_ = 15;
		break;
	default:
		return false;
	}
	
	// 일단 새로만든 룸데이터를 만들고 여기에 값을 복사하도록 깊은복사를 만드는식으로?
	for (int i = 0; i < CurrentMapCount_; i++)
	{
		std::vector<RoomData::Tile> TmpTileVector = AllMaps_[CurrentFloor_ - 1][0]->AllBlock_;
		for (int j = 0; j < TmpTileVector.size(); j++)
		{
		 	float4 TmpPos = float4(static_cast<float>(StartX + ScaleX * TmpTileVector[j].X_), static_cast<float>(StartY + ScaleY * TmpTileVector[j].Y_));
			CreateRenderer("rocks_basement_Test.bmp", RenderPivot::CENTER, TmpPos);
		}
	}
	
	return true;
}

float4 RandomRoomManager::RandomPos()
{
	return float4();
}

RandomRoomManager::RandomRoomManager()
	: CurrentMapPos_()
	, CurrentFloor_(0)
	, CurrentMapCount_(0)
{
}

RandomRoomManager::~RandomRoomManager()
{
	std::map<int, std::vector<RoomData*>>::iterator BeginIter = AllMaps_.begin();
	std::map<int, std::vector<RoomData*>>::iterator EndIter = AllMaps_.end();
	for (; BeginIter != EndIter; ++BeginIter)
	{
		std::vector<RoomData*>& TmpGroup = BeginIter->second;
		
		std::vector<RoomData*>::iterator BeginVectorIter = TmpGroup.begin();
		std::vector<RoomData*>::iterator EndVectorIter = TmpGroup.end();
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

void RandomRoomManager::Start()
{
	{
		std::vector<RoomData*> TmpVector;
	
		RoomData* TmpData = new RoomData();
		for (int y = 0; y < 7; y++)
		{
			for (int x = 0; x < 13; x++)
			{
				TmpData->AddBlock(x, y, TileType::Stone);
			}
		}
		TmpVector.push_back(TmpData);
	
		AllMaps_.insert(make_pair(0, TmpVector));
	}
}