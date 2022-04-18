#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "RoomData.h"
#include "Stone.h"
#include "RoomActor.h"

RandomRoomManager* RandomRoomManager::Inst_ = nullptr;

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
	
	// ⑷營 類曖 裘熱虜躑 奩犒
	for (int i = 0; i < CurrentMapCount_; i++)
	{
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomData());
		TmpActor->SetPos(RandomPos());

		CurrentMaps_.push_back(TmpActor);
	}
	
	for (int i = 0; i < CurrentMaps_.size(); i++)
	{
		CurrentMaps_[i]->Setting();
	}

	return true;
}


float4 RandomRoomManager::RandomPos()
{
	float4 ReturnPos;

	if (CurrentMaps_.size() == 0)
	{
		ReturnPos.x = 0;
		ReturnPos.y = 0;
		return ReturnPos;
	}

	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(CurrentMaps_.size() - 1));
	
	int RandomDir = GameEngineRandom::MainRandom->RandomInt(0, 3);
	for (int i = 0; i < 4; i++)
	{
		float4 TmpPos = CurrentMaps_[RandomInt]->GetPos();

		if (RandomDir == 0)
		{
			TmpPos += {0, 1};
		}
		else if (RandomDir == 1)
		{
			TmpPos += {0, -1};
		}
		else if (RandomDir == 2)
		{
			TmpPos += {1, 0};
		}
		else if (RandomDir == 3)
		{
			TmpPos += {-1, 0};
		}

		
		if (true == ExistPos(TmpPos))
		{
			RandomDir = (RandomDir + 1) % 4;
		}
		else
		{
			return TmpPos;
		}
	}

	return ReturnPos;
}
RoomData RandomRoomManager::RandomData()
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllMaps_[CurrentFloor_ - 1].size() - 1));
	RoomData RandomData = AllMaps_[CurrentFloor_ - 1][RandomInt];
	return RandomData;
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
	// 0類
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

bool RandomRoomManager::ExistPos(float4 _Pos)
{
	for (int i = 0; i < CurrentMaps_.size(); i++)
	{
		if (true == CurrentMaps_[i]->GetPos().CompareInt2D(_Pos))
		{
			return true;
		}
	}

	return false;
}