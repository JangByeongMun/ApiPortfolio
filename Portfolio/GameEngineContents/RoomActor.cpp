#include "RoomActor.h"
#include "Stone.h"
#include "RandomRoomManager.h"
#include "Door.h"
#include "Pooter.h"
#include "ContentsEnum.h"
#include "Fire.h"
#include "PassiveItem.h"
#include "Monstro.h"

float StartX = -420.0f;
float StartY = -225.0f;
float ScaleX = 70.0f;
float ScaleY = 75.0f;

RoomActor::RoomActor()
	: MonsterCount_(0)
	, BossCount_(0)
{
}

RoomActor::~RoomActor()
{
}

void RoomActor::MinusMonsterCount()
{
	MonsterCount_ -= 1;

	if (MonsterCount_ <= 0)
	{
		MonsterCount_ = 0;

		if (BossCount_ <= 0)
		{
			for (int i = 0; i < DoorVector_.size(); i++)
			{
				DoorVector_[i]->DoorOpen();
			}
		}
	}
}

void RoomActor::MinusBossCount()
{
	BossCount_ -= 1;

	if (BossCount_ <= 0)
	{
		BossCount_ = 0;

		if (MonsterCount_ <= 0)
		{
			for (int i = 0; i < DoorVector_.size(); i++)
			{
				DoorVector_[i]->DoorOpen();
			}
		}
	}
}

void RoomActor::Setting()
{
	float4 TmpRenderPos = { Pos_.x * 1280, Pos_.y * 740 };
	SetPosition(TmpRenderPos + GameEngineWindow::GetScale().Half());

	CreateRenderer("bgblack.bmp", RenderPivot::CENTER, float4::ZERO, -1);
	CreateRenderer("01_basement.bmp", RenderPivot::CENTER, float4::ZERO);

	// 문닫혀있을때 벽 평평하게 만드는 컬리젼추가
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Wall", { 1000, 80 });
		TmpCollision_->SetPivot(float4(0, 300) + float4(0, -5));
		CloseCollisionVector_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Wall", { 1000, 80 });
		TmpCollision_->SetPivot(float4(0, -300) + float4(0, -52));
		CloseCollisionVector_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Wall", { 80, 600 });
		TmpCollision_->SetPivot(float4(500, 0) + float4(16, 0));
		CloseCollisionVector_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Wall", { 80, 600 });
		TmpCollision_->SetPivot(float4(-500, 0) + float4(-19, 0));
		CloseCollisionVector_.push_back(TmpCollision_);
	}

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
		{
			Fire* TmpFire = GetLevel()->CreateActor<Fire>();
			TmpFire->SetPosition(GetPosition() + TmpTilePos);
			break;
		}
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
	MonsterCount_ = static_cast<int>(TmpMonsterVector.size());
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

	// 패시브 아이템 세팅
	std::vector<RoomData::PassiveData> TmpPassiveVector = Data_.AllPassives_;
	for (int i = 0; i < TmpPassiveVector.size(); i++)
	{
		float4 TmpTilePos = { StartX + ScaleX * TmpPassiveVector[i].X_, StartY + ScaleY * TmpPassiveVector[i].Y_ };
		PassiveItem* TmpPassiveItem = GetLevel()->CreateActor<PassiveItem>();
		TmpPassiveItem->SetPosition(GetPosition() + TmpTilePos);
		TmpPassiveItem->Setting(TmpPassiveVector[i].Type_);
	}

	// 보스몬스터 세팅
	std::vector<RoomData::BossData> TmpBossVector = Data_.AllBoss_;
	BossCount_ = static_cast<int>(TmpBossVector.size());
	for (int i = 0; i < TmpBossVector.size(); i++)
	{
		float4 TmpTilePos = { StartX + ScaleX * TmpBossVector[i].X_, StartY + ScaleY * TmpBossVector[i].Y_ };
		switch (TmpBossVector[i].Type_)
		{
		case BossType::Default:
			break;

		case BossType::Monstro:
		{
			Monstro* TmpBoss = GetLevel()->CreateActor<Monstro>();
			TmpBoss->SetPosition(GetPosition() + TmpTilePos);
			TmpBoss->SetRoom(*this);
			break;
		}

		case BossType::Max:
			break;
		default:
			break;
		}
	}

	if (BossCount_ != 0)
	{
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer("ui_bosshealthbar_Shadow.bmp", static_cast<int>(ORDER::UI), RenderPivot::Left);
			TmpRenderer->SetPivot({ -230, -300 });
			TmpRenderer->SetAlpha(150);
			BossHpRendererVector_.push_back(TmpRenderer);
		}
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer("ui_bosshealthbar.bmp", static_cast<int>(ORDER::UI), RenderPivot::Left);
			TmpRenderer->SetPivot({ -230, -300 });
			TmpRenderer->SetIndex(1);
			BossHpRendererVector_.push_back(TmpRenderer);
		}
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer("ui_bosshealthbar_2.bmp", static_cast<int>(ORDER::UI), RenderPivot::Left);
			TmpRenderer->SetPivot({ -170, -300 });
			BossHpRendererVector_.push_back(TmpRenderer);
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

void RoomActor::OpenAllDoor()
{
	for (int i = 0; i < DoorVector_.size(); i++)
	{
		DoorVector_[i]->DoorOpen();
	}
}

void RoomActor::CloseAllDoor()
{
	for (int i = 0; i < DoorVector_.size(); i++)
	{
		DoorVector_[i]->DoorClose();
	}
}

void RoomActor::SetBossHPUI(float _Value)
{
	BossHpRendererVector_[2]->SetIndexWithValue(0, {-1.0f, -1.0f}, _Value);
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
			TmpDoor->SetLock(true);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Down);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Down);
			break;
		}

		TmpDoor->SetCloseCollision(CloseCollisionVector_[0]);
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
			TmpDoor->SetLock(true);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Up);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Up);
			break;
		}

		TmpDoor->SetCloseCollision(CloseCollisionVector_[1]);
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
			TmpDoor->SetLock(true);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Right);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Right);
			break;
		}

		TmpDoor->SetCloseCollision(CloseCollisionVector_[2]);
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
			TmpDoor->SetLock(true);
			break;
		case RoomType::Boss:
			TmpDoor->Setting(DoorType::Boss, DoorDir::Left);
			break;
		default:
			TmpDoor->Setting(DefaultDoorType, DoorDir::Left);
			break;
		}

		TmpDoor->SetCloseCollision(CloseCollisionVector_[3]);
		DoorVector_.push_back(TmpDoor);
	}

	OpenAllDoor();
}
