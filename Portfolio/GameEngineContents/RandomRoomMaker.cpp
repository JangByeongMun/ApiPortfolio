#include "RandomRoomManager.h"
#include "RoomData.h"

void RandomRoomManager::MakeRooms()
{
	// 1층
	{
		// 기본방
		{
			std::vector<RoomData> TmpVector;

			//{
			//	RoomData TmpData = RoomData();
			//	for (int y = 1; y < 3; y++)
			//	{
			//		for (int x = 4; x < 9; x++)
			//		{
			//			TmpData.AddBlock(x, y, BlockType::STONE);
			//		}
			//	}
			//	TmpData.AddMonster(0, 0, MonsterType::Pooter);

			//	TmpVector.push_back(TmpData);
			//}

			//{
			//	RoomData TmpData = RoomData();
			//	TmpData.AddBlock(0, 0, BlockType::STONE);
			//	TmpData.AddMonster(0, 0, MonsterType::Pooter);

			//	TmpVector.push_back(TmpData);
			//}

			//{
			//	RoomData TmpData = RoomData();
			//	TmpData.AddBlock(12, 6, BlockType::STONEBLACK);
			//	TmpData.AddMonster(12, 5, MonsterType::Pooter);

			//	TmpVector.push_back(TmpData);
			//}

			//{
			//	RoomData TmpData = RoomData();
			//	TmpData.AddBlock(0, 1, BlockType::STONEBLACK);
			//	TmpData.AddBlock(0, 5, BlockType::STONE);
			//	TmpData.AddBlock(12, 1, BlockType::STONE);
			//	TmpData.AddBlock(12, 5, BlockType::STONE);
			//	TmpData.AddMonster(3, 3, MonsterType::Pooter);

			//	TmpVector.push_back(TmpData);
			//}

			//{
			//	RoomData TmpData = RoomData();

			//	TmpData.AddBlock(0, 5, BlockType::POOP);
			//	TmpData.AddBlock(1, 6, BlockType::POOP);
			//	TmpData.AddBlock(11, 0, BlockType::POOP);
			//	TmpData.AddBlock(12, 1, BlockType::POOP);
			//	
			//	TmpData.AddBlock(5, 2, BlockType::POOP);
			//	TmpData.AddBlock(6, 2, BlockType::POOP);
			//	TmpData.AddBlock(7, 2, BlockType::POOP);
			//	TmpData.AddBlock(5, 3, BlockType::POOP);
			//	TmpData.AddBlock(7, 3, BlockType::POOP);
			//	TmpData.AddBlock(5, 4, BlockType::POOP);
			//	TmpData.AddBlock(6, 4, BlockType::POOP);
			//	TmpData.AddBlock(7, 4, BlockType::POOP);

			//	TmpData.AddMonster(0, 0, MonsterType::Pooter);

			//	TmpVector.push_back(TmpData);
			//}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 5, BlockType::POOP);
				TmpData.AddBlock(1, 6, BlockType::POOP);
				TmpData.AddBlock(11, 0, BlockType::POOP);
				TmpData.AddBlock(12, 1, BlockType::POOP);

				TmpData.AddBlock(5, 2, BlockType::POOP);
				TmpData.AddBlock(6, 2, BlockType::POOP);
				TmpData.AddBlock(7, 2, BlockType::POOP);
				TmpData.AddBlock(5, 3, BlockType::POOP);
				TmpData.AddBlock(7, 3, BlockType::POOP);
				TmpData.AddBlock(5, 4, BlockType::POOP);
				TmpData.AddBlock(6, 4, BlockType::POOP);
				TmpData.AddBlock(7, 4, BlockType::POOP);

				TmpData.AddMonster(6, 3, MonsterType::Gaper);
				TmpData.AddMonster(6, 6, MonsterType::Sucker);

				TmpVector.push_back(TmpData);
			}

			AllRooms_.insert({ 0, TmpVector });
		}

		// 상점
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

				TmpData.AddPassive(6, 4);

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
				TmpData.AddBoss(0, 0, BossType::Monstro);

				TmpData.RoomType_ = RoomType::Boss;
				TmpVector.push_back(TmpData);
			}
			AllBossRooms_.insert({ 0, TmpVector });
		}
	}

	// 2층
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

			AllRooms_.insert({ 1, TmpVector });
		}

		// 상점
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

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}
			AllTreasureRooms_.insert({ 1, TmpVector });
		}

		// 보스방
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

	// 3층
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

			AllRooms_.insert({ 2, TmpVector });
		}

		// 상점
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

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}
			AllTreasureRooms_.insert({ 2, TmpVector });
		}

		// 보스방
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