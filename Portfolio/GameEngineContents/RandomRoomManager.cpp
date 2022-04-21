#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "RoomData.h"
#include "Stone.h"
#include "RoomActor.h"
#include "Player.h"
#include "PlayerUI.h"

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
	
	// 현재 층의 맵수만큼 반복
	for (int i = 0; i < CurrentMapCount_ - 2; i++)
	{
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomData());
		TmpActor->SetPos(RandomPos());

		CurrentRooms_.push_back(TmpActor);
	}

	// 황금방, 보스룸은 연결된 방이 1개인 곳으로 추가
	{ // 황금방
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomTreasureRoomData());
		TmpActor->SetPos(RandomCornerPos());

		CurrentRooms_.push_back(TmpActor);
	}
	{ // 보스방
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomBossRoomData());
		TmpActor->SetPos(RandomCornerPos());

		CurrentRooms_.push_back(TmpActor);
	}

	for (int i = 0; i < CurrentRooms_.size(); i++)
	{
		CurrentRooms_[i]->Setting();
	}
	Player::MainPlayer->GetPlayerUI()->SetMiniMap();
	return true;
}

float4 RandomRoomManager::RandomPos()
{
	float4 ReturnPos;

	if (CurrentRooms_.size() == 0)
	{
		ReturnPos.x = 0;
		ReturnPos.y = 0;
		return ReturnPos;
	}

	// 근처에 모든 방이 있는방을 제외한 랜덤한 방 인덱스 
	int RandomInt = 0;
	do
	{
		RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(CurrentRooms_.size() - 1));
	} while (4 == ConnectedRoomCount(CurrentRooms_[RandomInt]->GetPos()));

	int RandomDir = GameEngineRandom::MainRandom->RandomInt(0, 3);
	for (int i = 0; i < 4; i++)
	{
		float4 TmpPos = CurrentRooms_[RandomInt]->GetPos();

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
float4 RandomRoomManager::RandomCornerPos()
{
	// 방을 못찾았을때 다시 돌리도록
	while (true)
	{
		// 근처에 모든 방이 있는방을 제외하고, 특수방이 아닌 방 인덱스
		int RandomInt = 0;
		do
		{
			RandomInt = GameEngineRandom::MainRandom->RandomInt(1, static_cast<int>(CurrentRooms_.size() - 1));
		} while (
			4 == ConnectedRoomCount(CurrentRooms_[RandomInt]->GetPos()) ||
			false == CurrentRooms_[RandomInt]->GetData().IsDefaultType()
			);

		int RandomDir = GameEngineRandom::MainRandom->RandomInt(0, 3);
		for (int i = 0; i < 4; i++)
		{
			float4 TmpPos = CurrentRooms_[RandomInt]->GetPos();

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

			if (true == ExistPos(TmpPos)) // 이미 해당위치에 방이 존재할때
			{
				RandomDir = (RandomDir + 1) % 4;
			}
			else // 방이 없을경우
			{
				if (1 == ConnectedRoomCount(TmpPos)) // 해당 위치랑 이어진 방이 1개 뿐일경우()
				{
					return TmpPos;
				}
				else
				{
					RandomDir = (RandomDir + 1) % 4;
				}
			}
		}
	}

	MsgBoxAssert("코너방을 못찾았습니다.");
	return { 0, 0 };
}

RoomData RandomRoomManager::RandomData()
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllRooms_[CurrentFloor_ - 1].size() - 1));
	RoomData RandomData = AllRooms_[CurrentFloor_ - 1][RandomInt];
	return RandomData;
}
RoomData RandomRoomManager::RandomTreasureRoomData()
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllTreasureRooms_[CurrentFloor_ - 1].size() - 1));
	RoomData RandomData = AllTreasureRooms_[CurrentFloor_ - 1][RandomInt];
	return RandomData;
}
RoomData RandomRoomManager::RandomBossRoomData()
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllBossRooms_[CurrentFloor_ - 1].size() - 1));
	RoomData RandomData = AllBossRooms_[CurrentFloor_ - 1][RandomInt];
	return RandomData;
}

RandomRoomManager::RandomRoomManager()
	: CurrentFloor_(0)
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
	// 0층
	{
		// 기본방
		{
			std::vector<RoomData> TmpVector;

			{
				RoomData TmpData = RoomData();
				for (int y = 1; y < 3; y++)
				{
					for (int x = 4; x < 9; x++)
					{
						TmpData.AddBlock(x, y, BlockType::STONE);
					}
				}
				TmpData.AddMonster(0, 0, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddMonster(0, 0, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(12, 6, BlockType::STONEBLACK);
				TmpData.AddMonster(12, 5, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 1, BlockType::STONEBLACK);
				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);
				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddMonster(3, 3, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

			AllRooms_.insert({ 0, TmpVector });
		}
		
		// 황금방
		{
			std::vector<RoomData> TmpVector;
			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(3, 1, BlockType::STONE);
				TmpData.AddBlock(4, 1, BlockType::STONE);
				TmpData.AddBlock(5, 1, BlockType::STONE);
				TmpData.AddBlock(6, 1, BlockType::STONE);
				TmpData.AddBlock(7, 1, BlockType::STONE);
				TmpData.AddBlock(8, 1, BlockType::STONE);
				TmpData.AddBlock(9, 1, BlockType::STONE);

				TmpData.AddBlock(3, 2, BlockType::STONE);
				TmpData.AddBlock(4, 2, BlockType::STONE);
				TmpData.AddBlock(5, 2, BlockType::STONEURN);
				TmpData.AddBlock(6, 2, BlockType::FIRE);
				TmpData.AddBlock(7, 2, BlockType::STONEURN);
				TmpData.AddBlock(8, 2, BlockType::STONE);
				TmpData.AddBlock(9, 2, BlockType::STONE);

				TmpData.AddBlock(3, 3, BlockType::STONEURN);
				TmpData.AddBlock(4, 3, BlockType::FIRE);
				TmpData.AddBlock(8, 3, BlockType::FIRE);
				TmpData.AddBlock(9, 3, BlockType::STONEURN);

				TmpData.AddMonster(3, 3, MonsterType::Pooter);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}
			AllTreasureRooms_.insert({ 0, TmpVector });
		}

		// 보스방
		{
			std::vector<RoomData> TmpVector;
			{
				RoomData TmpData = RoomData();
				TmpData.AddMonster(0, 0, MonsterType::Pooter);

				TmpData.RoomType_ = RoomType::Boss;
				TmpVector.push_back(TmpData);
			}
			AllBossRooms_.insert({ 0, TmpVector });
		}
	}
}
bool RandomRoomManager::ExistPos(float4 _Pos)
{
	for (int i = 0; i < CurrentRooms_.size(); i++)
	{
		if (true == CurrentRooms_[i]->GetPos().CompareInt2D(_Pos))
		{
			return true;
		}
	}

	return false;
}
bool RandomRoomManager::CornerPos(float4 _Pos)
{
	int ConnectedCount = 0;
	if (true == ExistPos(_Pos + float4(0, 1)))
	{
		ConnectedCount += 1;
	}
	if (true == ExistPos(_Pos + float4(0, -1)))
	{
		ConnectedCount += 1;
	}
	if (true == ExistPos(_Pos + float4(1, 0)))
	{
		ConnectedCount += 1;
	}
	if (true == ExistPos(_Pos + float4(-1, 0)))
	{
		ConnectedCount += 1;
	}

	return (ConnectedCount == 1);
}
int RandomRoomManager::ConnectedRoomCount(float4 _Pos)
{
	int ConnectedCount = 0;
	if (true == ExistPos(_Pos + float4(0, 1)))
	{
		ConnectedCount += 1;
	}
	if (true == ExistPos(_Pos + float4(0, -1)))
	{
		ConnectedCount += 1;
	}
	if (true == ExistPos(_Pos + float4(1, 0)))
	{
		ConnectedCount += 1;
	}
	if (true == ExistPos(_Pos + float4(-1, 0)))
	{
		ConnectedCount += 1;
	}

	return ConnectedCount;
}

RoomActor* RandomRoomManager::FindRoom(float4 _Pos)
{
	for (int i = 0; i < CurrentRooms_.size(); i++)
	{
		if (true == CurrentRooms_[i]->GetPos().CompareInt2D(_Pos))
		{
			return CurrentRooms_[i];
		}
	}

	return nullptr;
}
RoomActor* RandomRoomManager::GetCurrentRoom()
{
	return FindRoom(Player::MainPlayer->GetCurrentRoomPos());
}
