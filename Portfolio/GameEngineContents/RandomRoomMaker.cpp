#include "RandomRoomManager.h"
#include "RoomData.h"

void RandomRoomManager::MakeRooms()
{
	// 1층
	{
		// 기본방
		{
			std::vector<RoomData> TmpVector;

			/*{
				RoomData TmpData = RoomData();

				TmpData.AddMonster(0, 1, MonsterType::Pooter);
				TmpData.AddMonster(12, 5, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

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

				TmpData.AddMonster(0, 0, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

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
				TmpData.AddMonster(6, 6, MonsterType::RoundWorm);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(4, 0, BlockType::STONE);
				TmpData.AddBlock(5, 0, BlockType::STONE);
				TmpData.AddBlock(7, 0, BlockType::STONE);
				TmpData.AddBlock(8, 0, BlockType::STONE);

				TmpData.AddBlock(0, 1, BlockType::STONE);
				TmpData.AddBlock(1, 1, BlockType::STONE);
				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(3, 1, BlockType::STONE);
				TmpData.AddBlock(9, 1, BlockType::STONE);
				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 5, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);
				TmpData.AddBlock(3, 5, BlockType::STONE);
				TmpData.AddBlock(9, 5, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);
				TmpData.AddBlock(12, 5, BlockType::STONE);

				TmpData.AddBlock(4, 6, BlockType::STONE);
				TmpData.AddBlock(5, 6, BlockType::STONE);
				TmpData.AddBlock(7, 6, BlockType::STONE);
				TmpData.AddBlock(8, 6, BlockType::STONE);

				TmpData.AddMonster(0, 0, MonsterType::RoundWorm);
				TmpData.AddMonster(0, 6, MonsterType::RoundWorm);
				TmpData.AddMonster(12, 0, MonsterType::RoundWorm);
				TmpData.AddMonster(12, 6, MonsterType::RoundWorm);

				TmpData.AddPickup(1, 0, ItemType::Money);
				TmpData.AddPickup(2, 0, ItemType::Money);
				TmpData.AddPickup(3, 0, ItemType::Money);
				TmpData.AddPickup(9, 6, ItemType::Money);
				TmpData.AddPickup(10, 6, ItemType::Money);
				TmpData.AddPickup(11, 6, ItemType::Money);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 1, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(12, 5, BlockType::STONE);

				TmpData.AddMonster(6, 3, MonsterType::BoomFlyNormal);
				TmpData.AddMonster(4, 3, MonsterType::FlyRed);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);

				TmpData.AddMonster(4, 3, MonsterType::FlyRed);
				TmpData.AddMonster(5, 3, MonsterType::FlyRed);
				TmpData.AddMonster(6, 3, MonsterType::FlyRed);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::THORN);
				TmpData.AddBlock(0, 1, BlockType::THORN);

				TmpData.AddBlock(0, 5, BlockType::THORN);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::THORN);

				TmpData.AddBlock(11, 0, BlockType::THORN);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::THORN);

				TmpData.AddBlock(12, 5, BlockType::THORN);
				TmpData.AddBlock(11, 6, BlockType::THORN);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddPickup(5, 3, ItemType::Money);
				TmpData.AddPickup(6, 2, ItemType::Money);
				TmpData.AddPickup(6, 3, ItemType::Money);
				TmpData.AddPickup(6, 4, ItemType::Money);
				TmpData.AddPickup(7, 3, ItemType::Money);


				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(1, 1, BlockType::STONE);
				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(1, 2, BlockType::STONE);

				TmpData.AddBlock(1, 4, BlockType::STONE);
				TmpData.AddBlock(1, 5, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);

				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);
				TmpData.AddBlock(11, 2, BlockType::STONE);

				TmpData.AddBlock(11, 4, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);

				TmpData.AddBlock(5, 2, BlockType::FIRE);
				TmpData.AddBlock(5, 3, BlockType::THORN);
				TmpData.AddBlock(5, 4, BlockType::FIRE);
				TmpData.AddBlock(6, 2, BlockType::THORN);
				TmpData.AddPickup(6, 3, ItemType::keyMaster);
				TmpData.AddBlock(6, 4, BlockType::THORN);
				TmpData.AddBlock(7, 2, BlockType::FIRE);
				TmpData.AddBlock(7, 3, BlockType::THORN);
				TmpData.AddBlock(7, 4, BlockType::FIRE);

				TmpData.AddMonster(0, 0, MonsterType::Pooter);
				TmpData.AddMonster(0, 5, MonsterType::Pooter);
				TmpData.AddMonster(12, 0, MonsterType::Pooter);
				TmpData.AddMonster(12, 5, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(11, 2, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddMonster(11, 1, MonsterType::RoundWorm);


				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 4, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);

				TmpData.AddMonster(1, 5, MonsterType::RoundWorm);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(9, 0, BlockType::STONE);
				TmpData.AddBlock(10, 0, BlockType::STONE);
				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(9, 1, BlockType::STONE);
				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);

				TmpData.AddBlock(9, 3, BlockType::STONE);
				TmpData.AddBlock(10, 3, BlockType::STONE);
				TmpData.AddBlock(11, 3, BlockType::STONE);
				TmpData.AddBlock(9, 4, BlockType::STONE);
				TmpData.AddPickup(10, 4, ItemType::Bomb);
				TmpData.AddBlock(11, 4, BlockType::STONE);
				TmpData.AddBlock(9, 5, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);

				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(3, 1, BlockType::STONE);
				TmpData.AddBlock(4, 1, BlockType::STONE);
				TmpData.AddBlock(2, 2, BlockType::STONE);
				TmpData.AddPickup(3, 2, ItemType::Bomb);
				TmpData.AddBlock(4, 2, BlockType::STONE);
				TmpData.AddBlock(2, 3, BlockType::STONE);
				TmpData.AddBlock(3, 3, BlockType::STONE);
				TmpData.AddBlock(4, 3, BlockType::STONE);

				TmpData.AddBlock(2, 5, BlockType::STONE);
				TmpData.AddBlock(3, 5, BlockType::STONE);
				TmpData.AddBlock(4, 5, BlockType::STONE);
				TmpData.AddBlock(2, 6, BlockType::STONE);
				TmpData.AddBlock(3, 6, BlockType::STONE);
				TmpData.AddBlock(4, 6, BlockType::STONE);

				TmpData.AddMonster(0, 0, MonsterType::Gaper);
				TmpData.AddMonster(0, 5, MonsterType::Gaper);
				TmpData.AddMonster(12, 0, MonsterType::Gaper);
				TmpData.AddMonster(12, 5, MonsterType::Gaper);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);

				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddMonster(1, 1, MonsterType::Gaper);
				TmpData.AddMonster(1, 5, MonsterType::FlyRed);
				TmpData.AddMonster(11, 1, MonsterType::FlyRed);
				TmpData.AddMonster(11, 5, MonsterType::Gaper);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(6, 3, BlockType::HOLE);

				TmpData.AddMonster(1, 1, MonsterType::Gaper);
				TmpData.AddMonster(11, 5, MonsterType::Gaper);

				TmpVector.push_back(TmpData);
			}*/

			{
				RoomData TmpData = RoomData();

				TmpData.AddMonster(0, 1, MonsterType::FloatingKnight);
				TmpData.AddMonster(12, 5, MonsterType::FloatingKnight);

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

				TmpData.AddShop(4, 4, ShopType::Bomb);
				TmpData.AddShop(6, 4, ShopType::Key);
				TmpData.AddShop(8, 4, ShopType::Passive);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::FIRE);
				TmpData.AddBlock(0, 6, BlockType::FIRE);
				TmpData.AddBlock(12, 0, BlockType::FIRE);
				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddShop(4, 4, ShopType::Passive);
				TmpData.AddShop(6, 4, ShopType::Bomb);
				TmpData.AddShop(8, 4, ShopType::Bomb);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::FIRE);
				TmpData.AddBlock(0, 6, BlockType::FIRE);
				TmpData.AddBlock(12, 0, BlockType::FIRE);
				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddShop(4, 4, ShopType::Key);
				TmpData.AddShop(6, 4, ShopType::Heart);
				TmpData.AddShop(8, 4, ShopType::Bomb);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::FIRE);
				TmpData.AddBlock(0, 6, BlockType::FIRE);
				TmpData.AddBlock(12, 0, BlockType::FIRE);
				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddShop(4, 4, ShopType::Key);
				TmpData.AddShop(6, 4, ShopType::Heart);
				TmpData.AddShop(8, 4, ShopType::Bomb);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::POOP);
				TmpData.AddBlock(0, 6, BlockType::POOP);
				TmpData.AddBlock(12, 0, BlockType::POOP);
				TmpData.AddBlock(12, 6, BlockType::POOP);

				TmpData.AddShop(4, 4, ShopType::Key);
				TmpData.AddShop(6, 4, ShopType::Passive);
				TmpData.AddShop(8, 4, ShopType::Heart);

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

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::FIRE);

				TmpData.AddBlock(0, 6, BlockType::FIRE);

				TmpData.AddBlock(12, 0, BlockType::FIRE);

				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddBlock(5, 4, BlockType::FIRE);
				TmpData.AddBlock(7, 4, BlockType::FIRE);

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();


				TmpData.AddBlock(4, 4, BlockType::FIRE);
				TmpData.AddBlock(8, 4, BlockType::FIRE);

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

				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(2, 0, BlockType::STONE);
				TmpData.AddBlock(2, 6, BlockType::STONE);
				TmpData.AddBlock(10, 0, BlockType::STONE);
				TmpData.AddBlock(10, 6, BlockType::STONE);
				TmpData.AddBlock(12, 6, BlockType::STONE);

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

				TmpData.AddMonster(0, 0, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

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
				TmpData.AddMonster(6, 6, MonsterType::RoundWorm);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(4, 0, BlockType::STONE);
				TmpData.AddBlock(5, 0, BlockType::STONE);
				TmpData.AddBlock(7, 0, BlockType::STONE);
				TmpData.AddBlock(8, 0, BlockType::STONE);

				TmpData.AddBlock(0, 1, BlockType::STONE);
				TmpData.AddBlock(1, 1, BlockType::STONE);
				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(3, 1, BlockType::STONE);
				TmpData.AddBlock(9, 1, BlockType::STONE);
				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 5, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);
				TmpData.AddBlock(3, 5, BlockType::STONE);
				TmpData.AddBlock(9, 5, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);
				TmpData.AddBlock(12, 5, BlockType::STONE);

				TmpData.AddBlock(4, 6, BlockType::STONE);
				TmpData.AddBlock(5, 6, BlockType::STONE);
				TmpData.AddBlock(7, 6, BlockType::STONE);
				TmpData.AddBlock(8, 6, BlockType::STONE);

				TmpData.AddMonster(0, 0, MonsterType::RoundWorm);
				TmpData.AddMonster(0, 6, MonsterType::RoundWorm);
				TmpData.AddMonster(12, 0, MonsterType::RoundWorm);
				TmpData.AddMonster(12, 6, MonsterType::RoundWorm);

				TmpData.AddPickup(1, 0, ItemType::Money);
				TmpData.AddPickup(2, 0, ItemType::Money);
				TmpData.AddPickup(3, 0, ItemType::Money);
				TmpData.AddPickup(9, 6, ItemType::Money);
				TmpData.AddPickup(10, 6, ItemType::Money);
				TmpData.AddPickup(11, 6, ItemType::Money);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 1, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(12, 5, BlockType::STONE);

				TmpData.AddMonster(6, 3, MonsterType::BoomFlyNormal);
				TmpData.AddMonster(4, 3, MonsterType::FlyRed);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);

				TmpData.AddMonster(4, 3, MonsterType::FlyRed);
				TmpData.AddMonster(5, 3, MonsterType::FlyRed);
				TmpData.AddMonster(6, 3, MonsterType::FlyRed);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::THORN);
				TmpData.AddBlock(0, 1, BlockType::THORN);

				TmpData.AddBlock(0, 5, BlockType::THORN);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::THORN);

				TmpData.AddBlock(11, 0, BlockType::THORN);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::THORN);

				TmpData.AddBlock(12, 5, BlockType::THORN);
				TmpData.AddBlock(11, 6, BlockType::THORN);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddPickup(5, 3, ItemType::Money);
				TmpData.AddPickup(6, 2, ItemType::Money);
				TmpData.AddPickup(6, 3, ItemType::Money);
				TmpData.AddPickup(6, 4, ItemType::Money);
				TmpData.AddPickup(7, 3, ItemType::Money);


				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(1, 1, BlockType::STONE);
				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(1, 2, BlockType::STONE);

				TmpData.AddBlock(1, 4, BlockType::STONE);
				TmpData.AddBlock(1, 5, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);

				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);
				TmpData.AddBlock(11, 2, BlockType::STONE);

				TmpData.AddBlock(11, 4, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);

				TmpData.AddBlock(5, 2, BlockType::FIRE);
				TmpData.AddBlock(5, 3, BlockType::THORN);
				TmpData.AddBlock(5, 4, BlockType::FIRE);
				TmpData.AddBlock(6, 2, BlockType::THORN);
				TmpData.AddPickup(6, 3, ItemType::keyMaster);
				TmpData.AddBlock(6, 4, BlockType::THORN);
				TmpData.AddBlock(7, 2, BlockType::FIRE);
				TmpData.AddBlock(7, 3, BlockType::THORN);
				TmpData.AddBlock(7, 4, BlockType::FIRE);

				TmpData.AddMonster(0, 0, MonsterType::Pooter);
				TmpData.AddMonster(0, 5, MonsterType::Pooter);
				TmpData.AddMonster(12, 0, MonsterType::Pooter);
				TmpData.AddMonster(12, 5, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(11, 2, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddMonster(11, 1, MonsterType::RoundWorm);


				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 4, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);

				TmpData.AddMonster(1, 5, MonsterType::RoundWorm);

				TmpVector.push_back(TmpData);
			}


			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(9, 0, BlockType::STONE);
				TmpData.AddBlock(10, 0, BlockType::STONE);
				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(9, 1, BlockType::STONE);
				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);

				TmpData.AddBlock(9, 3, BlockType::STONE);
				TmpData.AddBlock(10, 3, BlockType::STONE);
				TmpData.AddBlock(11, 3, BlockType::STONE);
				TmpData.AddBlock(9, 4, BlockType::STONE);
				TmpData.AddPickup(10, 4, ItemType::Bomb);
				TmpData.AddBlock(11, 4, BlockType::STONE);
				TmpData.AddBlock(9, 5, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);

				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(3, 1, BlockType::STONE);
				TmpData.AddBlock(4, 1, BlockType::STONE);
				TmpData.AddBlock(2, 2, BlockType::STONE);
				TmpData.AddPickup(3, 2, ItemType::Bomb);
				TmpData.AddBlock(4, 2, BlockType::STONE);
				TmpData.AddBlock(2, 3, BlockType::STONE);
				TmpData.AddBlock(3, 3, BlockType::STONE);
				TmpData.AddBlock(4, 3, BlockType::STONE);

				TmpData.AddBlock(2, 5, BlockType::STONE);
				TmpData.AddBlock(3, 5, BlockType::STONE);
				TmpData.AddBlock(4, 5, BlockType::STONE);
				TmpData.AddBlock(2, 6, BlockType::STONE);
				TmpData.AddBlock(3, 6, BlockType::STONE);
				TmpData.AddBlock(4, 6, BlockType::STONE);

				TmpData.AddMonster(0, 0, MonsterType::Gaper);
				TmpData.AddMonster(0, 5, MonsterType::Gaper);
				TmpData.AddMonster(12, 0, MonsterType::Gaper);
				TmpData.AddMonster(12, 5, MonsterType::Gaper);

				TmpVector.push_back(TmpData);
			}


			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);

				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddMonster(1, 1, MonsterType::Gaper);
				TmpData.AddMonster(1, 5, MonsterType::FlyRed);
				TmpData.AddMonster(11, 1, MonsterType::FlyRed);
				TmpData.AddMonster(11, 5, MonsterType::Gaper);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(6, 3, BlockType::HOLE);

				TmpData.AddMonster(1, 1, MonsterType::Gaper);
				TmpData.AddMonster(11, 5, MonsterType::Gaper);

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

				TmpData.AddShop(4, 4, ShopType::Bomb);
				TmpData.AddShop(6, 4, ShopType::Key);
				TmpData.AddShop(8, 4, ShopType::Passive);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::FIRE);
				TmpData.AddBlock(0, 6, BlockType::FIRE);
				TmpData.AddBlock(12, 0, BlockType::FIRE);
				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddShop(4, 4, ShopType::Passive);
				TmpData.AddShop(6, 4, ShopType::Bomb);
				TmpData.AddShop(8, 4, ShopType::Bomb);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::FIRE);
				TmpData.AddBlock(0, 6, BlockType::FIRE);
				TmpData.AddBlock(12, 0, BlockType::FIRE);
				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddShop(4, 4, ShopType::Key);
				TmpData.AddShop(6, 4, ShopType::Heart);
				TmpData.AddShop(8, 4, ShopType::Bomb);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::FIRE);
				TmpData.AddBlock(0, 6, BlockType::FIRE);
				TmpData.AddBlock(12, 0, BlockType::FIRE);
				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddShop(4, 4, ShopType::Key);
				TmpData.AddShop(6, 4, ShopType::Heart);
				TmpData.AddShop(8, 4, ShopType::Bomb);

				TmpData.RoomType_ = RoomType::Shop;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();
				TmpData.AddBlock(0, 0, BlockType::POOP);
				TmpData.AddBlock(0, 6, BlockType::POOP);
				TmpData.AddBlock(12, 0, BlockType::POOP);
				TmpData.AddBlock(12, 6, BlockType::POOP);

				TmpData.AddShop(4, 4, ShopType::Key);
				TmpData.AddShop(6, 4, ShopType::Passive);
				TmpData.AddShop(8, 4, ShopType::Heart);

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

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::FIRE);

				TmpData.AddBlock(0, 6, BlockType::FIRE);

				TmpData.AddBlock(12, 0, BlockType::FIRE);

				TmpData.AddBlock(12, 6, BlockType::FIRE);

				TmpData.AddBlock(5, 4, BlockType::FIRE);
				TmpData.AddBlock(7, 4, BlockType::FIRE);

				TmpData.AddPassive(6, 4);

				TmpData.RoomType_ = RoomType::Treasure;
				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();


				TmpData.AddBlock(4, 4, BlockType::FIRE);
				TmpData.AddBlock(8, 4, BlockType::FIRE);

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

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddBoss(0, 0, BossType::Loki);

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

				TmpData.AddMonster(0, 0, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

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
				TmpData.AddMonster(6, 6, MonsterType::RoundWorm);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(4, 0, BlockType::STONE);
				TmpData.AddBlock(5, 0, BlockType::STONE);
				TmpData.AddBlock(7, 0, BlockType::STONE);
				TmpData.AddBlock(8, 0, BlockType::STONE);

				TmpData.AddBlock(0, 1, BlockType::STONE);
				TmpData.AddBlock(1, 1, BlockType::STONE);
				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(3, 1, BlockType::STONE);
				TmpData.AddBlock(9, 1, BlockType::STONE);
				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 5, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);
				TmpData.AddBlock(3, 5, BlockType::STONE);
				TmpData.AddBlock(9, 5, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);
				TmpData.AddBlock(12, 5, BlockType::STONE);

				TmpData.AddBlock(4, 6, BlockType::STONE);
				TmpData.AddBlock(5, 6, BlockType::STONE);
				TmpData.AddBlock(7, 6, BlockType::STONE);
				TmpData.AddBlock(8, 6, BlockType::STONE);

				TmpData.AddMonster(0, 0, MonsterType::RoundWorm);
				TmpData.AddMonster(0, 6, MonsterType::RoundWorm);
				TmpData.AddMonster(12, 0, MonsterType::RoundWorm);
				TmpData.AddMonster(12, 6, MonsterType::RoundWorm);

				TmpData.AddPickup(1, 0, ItemType::Money);
				TmpData.AddPickup(2, 0, ItemType::Money);
				TmpData.AddPickup(3, 0, ItemType::Money);
				TmpData.AddPickup(9, 6, ItemType::Money);
				TmpData.AddPickup(10, 6, ItemType::Money);
				TmpData.AddPickup(11, 6, ItemType::Money);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 1, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(12, 5, BlockType::STONE);

				TmpData.AddMonster(6, 3, MonsterType::BoomFlyNormal);
				TmpData.AddMonster(4, 3, MonsterType::FlyRed);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(1, 0, BlockType::STONE);
				TmpData.AddBlock(0, 1, BlockType::STONE);

				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);

				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddBlock(12, 5, BlockType::STONE);
				TmpData.AddBlock(11, 6, BlockType::STONE);

				TmpData.AddMonster(4, 3, MonsterType::FlyRed);
				TmpData.AddMonster(5, 3, MonsterType::FlyRed);
				TmpData.AddMonster(6, 3, MonsterType::FlyRed);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);
				TmpData.AddBlock(1, 0, BlockType::THORN);
				TmpData.AddBlock(0, 1, BlockType::THORN);

				TmpData.AddBlock(0, 5, BlockType::THORN);
				TmpData.AddBlock(0, 6, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::THORN);

				TmpData.AddBlock(11, 0, BlockType::THORN);
				TmpData.AddBlock(12, 0, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::THORN);

				TmpData.AddBlock(12, 5, BlockType::THORN);
				TmpData.AddBlock(11, 6, BlockType::THORN);
				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddPickup(5, 3, ItemType::Money);
				TmpData.AddPickup(6, 2, ItemType::Money);
				TmpData.AddPickup(6, 3, ItemType::Money);
				TmpData.AddPickup(6, 4, ItemType::Money);
				TmpData.AddPickup(7, 3, ItemType::Money);


				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(1, 1, BlockType::STONE);
				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(1, 2, BlockType::STONE);

				TmpData.AddBlock(1, 4, BlockType::STONE);
				TmpData.AddBlock(1, 5, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);

				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);
				TmpData.AddBlock(11, 2, BlockType::STONE);

				TmpData.AddBlock(11, 4, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);

				TmpData.AddBlock(5, 2, BlockType::FIRE);
				TmpData.AddBlock(5, 3, BlockType::THORN);
				TmpData.AddBlock(5, 4, BlockType::FIRE);
				TmpData.AddBlock(6, 2, BlockType::THORN);
				TmpData.AddPickup(6, 3, ItemType::keyMaster);
				TmpData.AddBlock(6, 4, BlockType::THORN);
				TmpData.AddBlock(7, 2, BlockType::FIRE);
				TmpData.AddBlock(7, 3, BlockType::THORN);
				TmpData.AddBlock(7, 4, BlockType::FIRE);

				TmpData.AddMonster(0, 0, MonsterType::Pooter);
				TmpData.AddMonster(0, 5, MonsterType::Pooter);
				TmpData.AddMonster(12, 0, MonsterType::Pooter);
				TmpData.AddMonster(12, 5, MonsterType::Pooter);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(11, 2, BlockType::STONE);
				TmpData.AddBlock(12, 1, BlockType::STONE);

				TmpData.AddMonster(11, 1, MonsterType::RoundWorm);


				TmpData.AddBlock(0, 5, BlockType::STONE);
				TmpData.AddBlock(1, 4, BlockType::STONE);
				TmpData.AddBlock(1, 6, BlockType::STONE);
				TmpData.AddBlock(2, 5, BlockType::STONE);

				TmpData.AddMonster(1, 5, MonsterType::RoundWorm);

				TmpVector.push_back(TmpData);
			}


			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(9, 0, BlockType::STONE);
				TmpData.AddBlock(10, 0, BlockType::STONE);
				TmpData.AddBlock(11, 0, BlockType::STONE);
				TmpData.AddBlock(9, 1, BlockType::STONE);
				TmpData.AddBlock(10, 1, BlockType::STONE);
				TmpData.AddBlock(11, 1, BlockType::STONE);

				TmpData.AddBlock(9, 3, BlockType::STONE);
				TmpData.AddBlock(10, 3, BlockType::STONE);
				TmpData.AddBlock(11, 3, BlockType::STONE);
				TmpData.AddBlock(9, 4, BlockType::STONE);
				TmpData.AddPickup(10, 4, ItemType::Bomb);
				TmpData.AddBlock(11, 4, BlockType::STONE);
				TmpData.AddBlock(9, 5, BlockType::STONE);
				TmpData.AddBlock(10, 5, BlockType::STONE);
				TmpData.AddBlock(11, 5, BlockType::STONE);

				TmpData.AddBlock(2, 1, BlockType::STONE);
				TmpData.AddBlock(3, 1, BlockType::STONE);
				TmpData.AddBlock(4, 1, BlockType::STONE);
				TmpData.AddBlock(2, 2, BlockType::STONE);
				TmpData.AddPickup(3, 2, ItemType::Bomb);
				TmpData.AddBlock(4, 2, BlockType::STONE);
				TmpData.AddBlock(2, 3, BlockType::STONE);
				TmpData.AddBlock(3, 3, BlockType::STONE);
				TmpData.AddBlock(4, 3, BlockType::STONE);

				TmpData.AddBlock(2, 5, BlockType::STONE);
				TmpData.AddBlock(3, 5, BlockType::STONE);
				TmpData.AddBlock(4, 5, BlockType::STONE);
				TmpData.AddBlock(2, 6, BlockType::STONE);
				TmpData.AddBlock(3, 6, BlockType::STONE);
				TmpData.AddBlock(4, 6, BlockType::STONE);

				TmpData.AddMonster(0, 0, MonsterType::Gaper);
				TmpData.AddMonster(0, 5, MonsterType::Gaper);
				TmpData.AddMonster(12, 0, MonsterType::Gaper);
				TmpData.AddMonster(12, 5, MonsterType::Gaper);

				TmpVector.push_back(TmpData);
			}


			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(0, 0, BlockType::STONE);

				TmpData.AddBlock(12, 6, BlockType::STONE);

				TmpData.AddMonster(1, 1, MonsterType::Gaper);
				TmpData.AddMonster(1, 5, MonsterType::FlyRed);
				TmpData.AddMonster(11, 1, MonsterType::FlyRed);
				TmpData.AddMonster(11, 5, MonsterType::Gaper);

				TmpVector.push_back(TmpData);
			}

			{
				RoomData TmpData = RoomData();

				TmpData.AddBlock(6, 3, BlockType::HOLE);

				TmpData.AddMonster(1, 1, MonsterType::Gaper);
				TmpData.AddMonster(11, 5, MonsterType::Gaper);

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
				TmpData.AddBoss(0, 0, BossType::Mom);

				TmpData.RoomType_ = RoomType::Boss;
				TmpVector.push_back(TmpData);
			}
			AllBossRooms_.insert({ 2, TmpVector });
		}
	}
}