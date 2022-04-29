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
	if (1 == _Floor)
	{
		Player::MainPlayer->SetPlayerInfo();
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

	// ���� ���� �ʼ���ŭ �ݺ�
	for (int i = 0; i < CurrentMapCount_ - 3; i++)
	{
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomData());
		TmpActor->SetPos(RandomPos());

		CurrentRooms_.push_back(TmpActor);
	}

	// ����, Ȳ�ݹ�, �������� ����� ���� 1���� ������ �߰�
	{ // Ȳ�ݹ�
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomTreasureRoomData());
		TmpActor->SetPos(RandomCornerPos());

		CurrentRooms_.push_back(TmpActor);
	}
	{ // ������
		RoomActor* TmpActor = GetLevel()->CreateActor<RoomActor>();
		TmpActor->SetData(RandomBossRoomData());
		TmpActor->SetPos(RandomBossPos());

		SelectedBossType = TmpActor->GetData().GetBossType();
		CurrentRooms_.push_back(TmpActor);
	}
	{ // ����
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

	// ��ó�� ��� ���� �ִ¹��� ������ ������ �� �ε��� 
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
	// ���� ��ã������ �ٽ� ��������
	while (true)
	{
		// ��ó�� ��� ���� �ִ¹��� �����ϰ�, Ư������ �ƴ� �� �ε���
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

			if (true == ExistPos(TmpPos)) // �̹� �ش���ġ�� ���� �����Ҷ�
			{
				RandomDir = (RandomDir + 1) % 4;
			}
			else // ���� �������
			{
				if (1 == ConnectedRoomCount(TmpPos)) // �ش� ��ġ�� �̾��� ���� 1�� ���ϰ��()
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

	MsgBoxAssert("�ڳʹ��� ��ã�ҽ��ϴ�.");
	return { 0, 0 };
}
float4 RandomRoomManager::RandomBossPos()
{
	// �������� ���۹濡 �Ⱥپ��ֵ��� �߰��� ���
 
	// ���� ��ã������ �ٽ� ��������
	while (true)
	{
		// ��ó�� ��� ���� �ִ¹��� �����ϰ�, Ư������ �ƴ� �� �ε���
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

			if (true == ExistPos(TmpPos)) // �̹� �ش���ġ�� ���� �����Ҷ�
			{
				RandomDir = (RandomDir + 1) % 4;
			}
			else // ���� �������
			{
				if (1 == ConnectedRoomCount(TmpPos)) // �ش� ��ġ�� �̾��� ���� 1�� ���ϰ��()
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

	MsgBoxAssert("�ڳʹ��� ��ã�ҽ��ϴ�.");
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
	// 1��
	{
		// �⺻��
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
		
		// ����
		{
			std::vector<RoomData> TmpVector;

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(1, 1, BlockType::FIRE);
				TmpData.AddBlock(11, 1, BlockType::FIRE);

				TmpData.AddShop(4, 3, ShopType::Bomb);
				TmpData.AddShop(6, 3, ShopType::Key);
				TmpData.AddShop(8, 3, ShopType::Passive);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			AllShopRooms_.insert({ 0, TmpVector });
		}

		// Ȳ�ݹ�
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

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}
			AllTreasureRooms_.insert({ 0, TmpVector });
		}

		// ������
		{
			std::vector<RoomData> TmpVector;
			{
				RoomData TmpData = RoomData();
				TmpData.AddBoss(0, 0, BossType::Monstro);

				TmpData.RoomType_ = RoomType::Boss;
				TmpVector.push_back(TmpData);
			}
			AllBossRooms_.insert({ 0, TmpVector });
		}
	}

	// 2��
	{
		// �⺻��
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

			AllRooms_.insert({ 1, TmpVector });
		}

		// ����
		{
			std::vector<RoomData> TmpVector;

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(1, 1, BlockType::FIRE);
				TmpData.AddBlock(11, 1, BlockType::FIRE);

				TmpData.AddShop(4, 3, ShopType::Bomb);
				TmpData.AddShop(6, 3, ShopType::Key);
				TmpData.AddShop(8, 3, ShopType::Passive);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			AllShopRooms_.insert({ 1, TmpVector });
		}

		// Ȳ�ݹ�
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

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}
			AllTreasureRooms_.insert({ 1, TmpVector });
		}

		// ������
		{
			std::vector<RoomData> TmpVector;
			{
				RoomData TmpData = RoomData();
				TmpData.AddBoss(0, 0, BossType::Monstro);

				TmpData.RoomType_ = RoomType::Boss;
				TmpVector.push_back(TmpData);
			}
			AllBossRooms_.insert({ 1, TmpVector });
		}
	}

	// 3��
	{
		// �⺻��
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

			AllRooms_.insert({ 2, TmpVector });
		}

		// ����
		{
			std::vector<RoomData> TmpVector;

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(1, 1, BlockType::FIRE);
				TmpData.AddBlock(11, 1, BlockType::FIRE);

				TmpData.AddShop(4, 3, ShopType::Bomb);
				TmpData.AddShop(6, 3, ShopType::Key);
				TmpData.AddShop(8, 3, ShopType::Passive);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			AllShopRooms_.insert({ 2, TmpVector });
		}

		// Ȳ�ݹ�
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

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}
			AllTreasureRooms_.insert({ 2, TmpVector });
		}

		// ������
		{
			std::vector<RoomData> TmpVector;
			{
				RoomData TmpData = RoomData();
				TmpData.AddBoss(0, 0, BossType::Monstro);

				TmpData.RoomType_ = RoomType::Boss;
				TmpVector.push_back(TmpData);
			}
			AllBossRooms_.insert({ 2, TmpVector });
		}
	}
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
		FloorRenderer_->Death();
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
