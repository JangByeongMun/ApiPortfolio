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

	// 문 세팅
	DoorSetting();

	// 시작방에선 오브젝트 안만들고 가이드 UI 생성
	// 생각해보니 생성할때 0, 0엔 빈방을 만들고 나머지를 랜덤으로 채우는게 좋았을듯
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
			TmpStone->Create(0);
			break;
		}
		case BlockType::STONEBLACK:
		{
			Stone* TmpStone = GetLevel()->CreateActor<Stone>();
			TmpStone->SetPosition(GetPosition() + TmpTilePos);
			TmpStone->Create(1);
			break;
		}
		case BlockType::STONEURN:
		{
			Stone* TmpStone = GetLevel()->CreateActor<Stone>();
			TmpStone->SetPosition(GetPosition() + TmpTilePos);
			TmpStone->Create(2);
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
	MonsterCount_ = TmpMonsterVector.size();
	for (int i = 0; i < TmpMonsterVector.size(); i++)
	{
		float4 TmpTilePos = { StartX + ScaleX * TmpMonsterVector[i].X_, StartY + ScaleY * TmpMonsterVector[i].Y_ };
		switch (TmpMonsterVector[i].Type_)
		{
		case MonsterType::Default:
			break;

		case MonsterType::Pooter:
		{
			Pooter* TmpMonster = GetLevel()->CreateActor<Pooter>();
			TmpMonster->SetPosition(GetPosition() + TmpTilePos);
			TmpMonster->SetRoom(*this);
			TmpMonster->SetMoveSpeed(10.0f);
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
	DoorType DefaultDoorType = DoorType::Default;
	// 자기방이 황금방이면 황금문
	if (RoomType::Treasure == Data_.RoomType_)
	{
		DefaultDoorType = DoorType::Treasure;
	}
	else if (RoomType::Boss == Data_.RoomType_)
	{
		DefaultDoorType = DoorType::Boss;
	}

	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(0, 1)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4( 0, 300 ));

		switch (RandomRoomManager::GetInst()->FindRoom(Pos_ + float4(0, 1))->Data_.RoomType_)
		{
		case RoomType::Treasure:
			TmpDoor->Setting(DoorType::Treasure, DoorDir::Down);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Down);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Down);
			break;
		}
		DoorVector_.push_back(TmpDoor);
	}
	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(0, -1)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4(0, -300));

		switch (RandomRoomManager::GetInst()->FindRoom(Pos_ + float4(0, -1))->Data_.RoomType_)
		{
		case RoomType::Treasure:
			TmpDoor->Setting(DoorType::Treasure, DoorDir::Up);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Up);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Up);
			break;
		}
		DoorVector_.push_back(TmpDoor);
	}
	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(1, 0)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4(500, 0));
		
		switch (RandomRoomManager::GetInst()->FindRoom(Pos_ + float4(1, 0))->Data_.RoomType_)
		{
		case RoomType::Treasure:
			TmpDoor->Setting(DoorType::Treasure, DoorDir::Right);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Right);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Right);
			break;
		}
		DoorVector_.push_back(TmpDoor);
	}
	if (true == RandomRoomManager::GetInst()->ExistPos(Pos_ + float4(-1, 0)))
	{
		Door* TmpDoor = GetLevel()->CreateActor<Door>(0);
		TmpDoor->SetPosition(GetPosition() + float4(-500, 0));
		
		switch (RandomRoomManager::GetInst()->FindRoom(Pos_ + float4(-1, 0))->Data_.RoomType_)
		{
		case RoomType::Treasure:
			TmpDoor->Setting(DoorType::Treasure, DoorDir::Left);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Left);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Left);
			break;
		}
		DoorVector_.push_back(TmpDoor);
	}
}
