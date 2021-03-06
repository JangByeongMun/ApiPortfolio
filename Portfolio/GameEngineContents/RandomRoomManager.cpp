#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "RoomData.h"
#include "Stone.h"
#include "RoomActor.h"
#include "Player.h"
#include "PlayerUI.h"
#include "ContentsGlobal.h"

RandomRoomManager* RandomRoomManager::Inst_ = nullptr;

void RandomRoomManager::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void RandomRoomManager::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Inst_ = nullptr;
	//Destroy();
}

bool RandomRoomManager::ChangeFloor(const int& _Floor)
{
	Player* TmpPlayer = Player::MainPlayer;
	if (1 == _Floor)
	{
		if (TmpPlayer != nullptr)
		{
			Player::MainPlayer->SetPlayerInfo();
		}
	}

	if (TmpPlayer != nullptr)
	{
		Player::MainPlayer->SetMasterkey(false);
	}

	switch (_Floor)
	{
	case 1:
		CurrentMapCount_ = 9;
		FloorName_ = "Basement1.bmp";
		break;
	case 2:
		CurrentMapCount_ = 12;
		FloorName_ = "Caves1.bmp";
		break;
	case 3:
		CurrentMapCount_ = 15;
		FloorName_ = "Depths1.bmp";
		break;
	default:
		return false;
	}
	AnimTimer_ = 0.0f;
	FloorRenderer_ = CreateRenderer(FloorName_, static_cast<int>(ORDER::UI), RenderPivot::CENTER, { -700, 0 });

	// 현재 층의 맵수만큼 반복
	for (int i = 0; i < CurrentMapCount_ - 3; i++)
	{
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomData());
		TmpActor->SetPos(RandomPos());

		CurrentRooms_.push_back(TmpActor);
	}

	// 상점, 황금방, 보스룸은 연결된 방이 1개인 곳으로 추가
	{ // 황금방
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomTreasureRoomData());
		TmpActor->SetPos(RandomCornerPos());

		CurrentRooms_.push_back(TmpActor);
	}
	{ // 보스방
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomBossRoomData());
		TmpActor->SetPos(RandomBossPos());

		SelectedBossType = TmpActor->GetData().GetBossType();
		CurrentRooms_.push_back(TmpActor);
	}
	{ // 상점
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomShopRoomData());
		TmpActor->SetPos(RandomCornerPos());

		CurrentRooms_.push_back(TmpActor);
	}

	for (int i = 0; i < CurrentRooms_.size(); i++)
	{
		CurrentRooms_[i]->Setting();
	}
	Player::MainPlayer->GetPlayerUI()->MakeMiniMap();
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
			RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(CurrentRooms_.size() - 1));
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
float4 RandomRoomManager::RandomBossPos()
{
	// 보스방은 시작방에 안붙어있도록 추가된 기능
 
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
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllRooms_[CurrentFloor - 1].size() - 1));
	RoomData RandomData = AllRooms_[CurrentFloor - 1][RandomInt];
	return RandomData;
}
RoomData RandomRoomManager::RandomTreasureRoomData()
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllTreasureRooms_[CurrentFloor - 1].size() - 1));
	RoomData RandomData = AllTreasureRooms_[CurrentFloor - 1][RandomInt];
	return RandomData;
}
RoomData RandomRoomManager::RandomBossRoomData()
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllBossRooms_[CurrentFloor - 1].size() - 1));
	RoomData RandomData = AllBossRooms_[CurrentFloor - 1][RandomInt];
	return RandomData;
}
RoomData RandomRoomManager::RandomShopRoomData()
{
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, static_cast<int>(AllShopRooms_[CurrentFloor - 1].size() - 1));
	RoomData RandomData = AllShopRooms_[CurrentFloor - 1][RandomInt];
	return RandomData;
}

RandomRoomManager::RandomRoomManager()
	: CurrentMapCount_(0)
	, AnimTimer_(-1.0f)
	, FloorRenderer_(nullptr)
{
}
RandomRoomManager::~RandomRoomManager()
{
}

void RandomRoomManager::Start()
{
	MakeRooms();
}
void RandomRoomManager::Update()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ <= 1.7f)
	{
		float4 LerpPos = float4::Lerp({ -900, -300 }, { 0, -300 }, AnimTimer_ * 4.0f);
		FloorRenderer_->SetPivot(LerpPos + GameEngineWindow::GetScale().Half());
	}
	else if (AnimTimer_ <= 2.0f)
	{
		float4 LerpPos = float4::Lerp({ 0, -300 }, { 900, -300 }, (AnimTimer_ - 1.7f) * 4.0f);
		FloorRenderer_->SetPivot(LerpPos + GameEngineWindow::GetScale().Half());
	}
	else
	{
		if (FloorRenderer_ != nullptr)
		{
			FloorRenderer_->Death();
			FloorRenderer_ = nullptr;
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
	if (false == ExistPos(_Pos))
	{
		return nullptr;
	}

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
