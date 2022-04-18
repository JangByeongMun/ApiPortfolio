#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "RoomData.h"
#include "Stone.h"

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
	
	// ÇöÀç ÃþÀÇ ¸Ê¼ö¸¸Å­ ¹Ýº¹
	for (int i = 0; i < CurrentMapCount_; i++)
	{
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllMaps_[CurrentFloor_ - 1].size() - 1));
		RoomData TmpTileVector = (AllMaps_[CurrentFloor_ - 1][RandomInt]);
		CurrentMaps_.insert({ RandomPos(), TmpTileVector });
	}

	RenderCurrentMaps();
	return true;
}


MapPos RandomRoomManager::RandomPos()
{
	MapPos ReturnPos = MapPos();

	if (CurrentMaps_.size() == 0)
	{
		ReturnPos.x = 0;
		ReturnPos.y = 0;
		return ReturnPos;
	}

	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(CurrentMaps_.size() - 1));
	std::map<MapPos, RoomData>::iterator findIter = CurrentMaps_.begin();
	for (int i = 0; i < RandomInt; i++)
	{
		findIter++;
	}
	
	MapPos FindPos = findIter->first;
	int RandomDir = GameEngineRandom::MainRandom->RandomInt(0, 3);
	for (int i = 0; i < 4; i++)
	{
		MapPos TmpPos = FindPos;

		if (RandomDir == 0)
		{
			TmpPos = MapPos(float4(static_cast<float>(FindPos.x), static_cast<float>(FindPos.y + 1)));
		}
		else if (RandomDir == 1)
		{
			TmpPos = MapPos(float4(static_cast<float>(FindPos.x), static_cast<float>(FindPos.y - 1)));
		}
		else if (RandomDir == 2)
		{
			TmpPos = MapPos(float4(static_cast<float>(FindPos.x + 1), static_cast<float>(FindPos.y)));
		}
		else if (RandomDir == 3)
		{
			TmpPos = MapPos(float4(static_cast<float>(FindPos.x - 1), static_cast<float>(FindPos.y)));
		}

		if (CurrentMaps_.end() == CurrentMaps_.find(TmpPos))
		{
			return TmpPos;
		}
		RandomDir = (RandomDir + 1) % 4;
	}

	return ReturnPos;
}

RandomRoomManager::RandomRoomManager()
	: CurrentMapPos_()
	, CurrentFloor_(0)
	, CurrentMapCount_(0)
{
}

RandomRoomManager::~RandomRoomManager()
{
	//std::map<int, std::vector<RoomData>>::iterator BeginIter = AllMaps_.begin();
	//std::map<int, std::vector<RoomData>>::iterator EndIter = AllMaps_.end();
	//for (; BeginIter != EndIter; ++BeginIter)
	//{
	//	std::vector<RoomData>& TmpGroup = BeginIter->second;
	//	
	//	std::vector<RoomData>::iterator BeginVectorIter = TmpGroup.begin();
	//	std::vector<RoomData>::iterator EndVectorIter = TmpGroup.end();
	//	for (; BeginVectorIter != EndVectorIter; ++BeginVectorIter)
	//	{
	//		if (nullptr == (*BeginVectorIter))
	//		{
	//			continue;
	//		}
	//
	//		delete (*BeginVectorIter);
	//		(*BeginVectorIter) = nullptr;
	//	}
	//}
}

void RandomRoomManager::Start()
{
	// 0Ãþ
	{
		std::vector<RoomData> TmpVector;

		{
			RoomData TmpData = RoomData();
			for (int y = 0; y < 7; y++)
			{
				for (int x = 0; x < 13; x++)
				{
					TmpData.AddBlock(x, y, BlockData::STONE);
				}
			}
			TmpVector.push_back(TmpData);
		}

		{
			RoomData TmpData = RoomData();
			TmpData.AddBlock(0, 0, BlockData::STONE);
			TmpVector.push_back(TmpData);
		}

		AllMaps_.insert(make_pair(0, TmpVector));
	}
}

void RandomRoomManager::RenderCurrentMaps()
{
	std::map<MapPos, RoomData>::iterator BeginIter = CurrentMaps_.begin();
	std::map<MapPos, RoomData>::iterator EndIter = CurrentMaps_.end();

	for (; BeginIter != EndIter; ++BeginIter)
	{
		float4 CurrentMapPos = { static_cast<float>(BeginIter->first.x * 1280) , static_cast<float>(BeginIter->first.y * 720) };
		CreateRenderer("01_basement.bmp", RenderPivot::CENTER, CurrentMapPos + GameEngineWindow::GetScale().Half());

		// ÇöÀç ¸Ê³»ºÎ ¹Ýº¹
		std::vector<RoomData::Tile> TmpTileVector = BeginIter->second.AllBlock_;
		for (int j = 0; j < TmpTileVector.size(); j++)
		{
		 	float4 TmpPos = float4(static_cast<float>(StartX + ScaleX * TmpTileVector[j].X_), static_cast<float>(StartY + ScaleY * TmpTileVector[j].Y_));
			
			switch (TmpTileVector[j].Type_)
			{
			case BlockData::STONE:
				GetLevel()->CreateActor<Stone>()->SetPosition(CurrentMapPos + TmpPos);
				break;
			default:
				break;
			}
		}
	}
}
