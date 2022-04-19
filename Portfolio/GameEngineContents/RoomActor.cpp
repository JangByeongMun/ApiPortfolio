#include "RoomActor.h"
#include "Stone.h"
#include "RandomRoomManager.h"
#include "Door.h"
#include "Pooter.h"
#include "ContentsEnum.h"


float StartX = -420.0f;
float StartY = -225.0f;
float ScaleX = 70.0f;
float ScaleY = 75.0f;

RoomActor::RoomActor()
{
}

RoomActor::~RoomActor()
{
}

void RoomActor::Setting()
{
	float4 TmpRenderPos = { Pos_.x * 1280, Pos_.y * 740 };
	SetPosition(TmpRenderPos + GameEngineWindow::GetScale().Half());

	CreateRenderer("bgblack.bmp", RenderPivot::CENTER, float4::ZERO, -1);
	CreateRenderer("01_basement.bmp", RenderPivot::CENTER, float4::ZERO);
	DoorSetting();

	if (Pos_.CompareInt2D({0, 0}))
	{
		CreateRenderer("StartGuide.bmp");
		return;
	}
	
	// 블럭 세팅
	std::vector<RoomData::BlockData> TmpTileVector = Data_.AllBlock_;
	for (int i = 0; i < TmpTileVector.size(); i++)
	{
		float4 TmpTilePos = { StartX + ScaleX * TmpTileVector[i].X_, StartY + ScaleY * TmpTileVector[i].Y_ };
		switch (TmpTileVector[i].Type_)
		{
		case BlockType::FIRE:
			break;
		case BlockType::HOLE:
			break;
		case BlockType::POOP:
			break;
		case BlockType::STONE:
		{
			Stone* TmpStone = GetLevel()->CreateActor<Stone>();
			TmpStone->SetPosition(GetPosition() + TmpTilePos);
			TmpStone->Create(false);
			break;
		}
		case BlockType::STONEBLACK:
		{
			Stone* TmpStone = GetLevel()->CreateActor<Stone>();
			TmpStone->SetPosition(GetPosition() + TmpTilePos);
			TmpStone->Create(true);
			break;
		}
		case BlockType::THORN:
			break;
		default:
			break;
		}
	}

	// 몬스터 세팅
	std::vector<RoomData::MonsterData> TmpMonsterVector = Data_.AllMonster_;
	for (int i = 0; i < TmpMonsterVector.size(); i++)
	{
		float4 TmpTilePos = { StartX + ScaleX * TmpTileVector[i].X_, StartY + ScaleY * TmpTileVector[i].Y_ };
		switch (TmpMonsterVector[i].Type_)
		{
		case MonsterType::Default:
			break;

		case MonsterType::Pooter:
		{
			Pooter* TmpMonster = GetLevel()->CreateActor<Pooter>();
			TmpMonster->SetPosition(GetPosition() + TmpTilePos);
			TmpMonster->SetRoom(*this);
			break;
		}

		case MonsterType::Max:
			break;

		default:
			break;
		}
	}
}

Door* RoomActor::FindDoor(DoorDir _Dir)
{
	for (int i = 0; i < DoorVector_.size(); i++)
	{
		if (_Dir == DoorVector_[i]->GetDir())
		{
			return DoorVector_[i];
		}
	}
	return nullptr;
}

bool RoomActor::IsCurrentRoom()
{
	return RandomRoomManager::GetInst()->GetCurrentRoom() == this;
}

void RoomActor::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
}

void RoomActor::DoorSetting()
{
	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(0, 1)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4( 0, 300 ));
		TmpDoor->Setting(DoorType::Default, DoorDir::Down);
		DoorVector_.push_back(TmpDoor);
	}
	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(0, -1)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4(0, -300));
		TmpDoor->Setting(DoorType::Default, DoorDir::Up);
		DoorVector_.push_back(TmpDoor);
	}
	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(1, 0)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4(500, 0));
		TmpDoor->Setting(DoorType::Default, DoorDir::Right);
		DoorVector_.push_back(TmpDoor);
	}
	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(-1, 0)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4(-500, 0));
		TmpDoor->Setting(DoorType::Default, DoorDir::Left);
		DoorVector_.push_back(TmpDoor);
	}
}
