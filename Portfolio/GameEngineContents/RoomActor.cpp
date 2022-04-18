#include "RoomActor.h"
#include "Stone.h"
#include "RandomRoomManager.h"
#include "Door.h"

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

	std::vector<RoomData::Tile> TmpTileVector = Data_.AllBlock_;
	for (int j = 0; j < TmpTileVector.size(); j++)
	{
		float4 TmpTilePos = { StartX + ScaleX * TmpTileVector[j].X_, StartY + ScaleY * TmpTileVector[j].Y_ };

		switch (TmpTileVector[j].Type_)
		{
		case BlockData::STONE:
			GetLevel()->CreateActor<Stone>()->SetPosition(GetPosition() + TmpTilePos);
			break;
		default:
			break;
		}
	}
	DoorSetting();
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
