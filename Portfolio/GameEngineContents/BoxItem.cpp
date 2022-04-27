#include "BoxItem.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include "Player.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "KeyItem.h"
#include "BombItem.h"
#include "MoneyItem.h"
#include "BatteryItem.h"

BoxItem::BoxItem() 
	: Type_(BoxType::Normal)
	, AnimTimer_(0.0f)
	, IsOpen_(false)
{
}

BoxItem::~BoxItem() 
{
}

void BoxItem::SetType(BoxType _Type)
{
	Type_ = _Type;
	switch (Type_)
	{
	case BoxType::Normal:
		RendererVector_[0]->On();
		RendererVector_[0]->ChangeAnimation("Appear");
		AnimTimer_ = 0.0f;
		break;
	case BoxType::Gold:
		RendererVector_[1]->On();
		RendererVector_[1]->ChangeAnimation("Appear");
		AnimTimer_ = 0.0f;
		break;
	default:
		break;
	}
}

void BoxItem::Start()
{
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_005_chests_Normal.bmp");
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Idle", 0, 0, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Open", 1, 1, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Appear", 6, 8, 0.1f, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Opening", 2, 4, 0.1f, false);
		TmpRenderer->ChangeAnimation("Idle");
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_005_chests_Gold.bmp");
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Idle", 0, 0, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Open", 1, 1, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Appear", 6, 8, 0.1f, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Opening", 2, 4, 0.1f, false);
		TmpRenderer->ChangeAnimation("Idle");
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}
}

void BoxItem::Update()
{
	if (false == IsOpen_) // ´ÝÇôÀÖÀ»‹š
	{
		AnimTimer_ += GameEngineTime::GetDeltaTime();
		if (AnimTimer_ >= 0.3f)
		{
			for (int i = 0; i < RendererVector_.size(); i++)
			{
				RendererVector_[i]->ChangeAnimation("Idle");
			}

			Collision_ = CreateCollision("Box", { 90, 60 });
		}

		// ¹Ú½º°¡ ÇÃ·¹ÀÌ¾î¶û Ãæµ¹ÇßÀ»¶§
		if (nullptr != Collision_ && true == Collision_->CollisionCheckRect("Player")) 
		{
			if (BoxType::Normal == Type_) // ³ë¸»¹Ú½º¸é ±×³É¿­¸²
			{
				IsOpen_ = true;
				AnimTimer_ = 0.0f;
				for (int i = 0; i < RendererVector_.size(); i++)
				{
					RendererVector_[i]->ChangeAnimation("Opening");
				}
				NormalBoxReward();
			}
			else if (BoxType::Gold == Type_) // È²±Ý¹Ú½º¸é Å°°¡ ÀÕ¾î¾ß ¿­¸°´Ù
			{
				if (true == Player::MainPlayer->HaveKey())
				{
					Player::MainPlayer->MinusItem(ItemType::Key, 1);
					IsOpen_ = true;
					AnimTimer_ = 0.0f;
					for (int i = 0; i < RendererVector_.size(); i++)
					{
						RendererVector_[i]->ChangeAnimation("Opening");
					}
					GoldBoxReward();
				}
			}
		}
	}
	else // ¿­·ÁÀÖÀ»¶§
	{
		AnimTimer_ += GameEngineTime::GetDeltaTime();
		if (AnimTimer_ >= 0.3f)
		{
			for (int i = 0; i < RendererVector_.size(); i++)
			{
				RendererVector_[i]->ChangeAnimation("Open");
			}
		}
	}

	// ¿ÀÇÂ¿©ºÎ »ó°ü¾øÀÌ ÇÃ·¹ÀÌ¾î¿Í Ãæµ¹ÇßÀ»¶§
	// ¹Ð¸®µµ·Ï ±¸Çö
	if (nullptr != Collision_ && true == Collision_->CollisionCheckRect("Player"))
	{
		float4 TmpDir = GetPosition() - Player::MainPlayer->GetPosition();
		TmpDir.Normal2D();
		AddDir(TmpDir * 2.0f);
	}
	SetObjectMove();
}

void BoxItem::NormalBoxReward()
{
	float RandomFloat = GameEngineRandom::MainRandom->RandomFloat(0.0f, 1.0f);
	if (0.0f <= RandomFloat && RandomFloat < 0.15f)
	{
		// ¿­¼è 1°³
		KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
		TmpObject->SetType(KeyType::Normal);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.15f <= RandomFloat && RandomFloat < 0.3f)
	{
		// ÆøÅº 1°³
		BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
		TmpObject->SetType(BombType::Normal);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.3f <= RandomFloat && RandomFloat < 0.45f)
	{
		// 3¿ø
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.45f <= RandomFloat && RandomFloat < 0.5f)
	{
		// ¿­¼è 2°³
		KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
		TmpObject->SetType(KeyType::Two);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.5f <= RandomFloat && RandomFloat < 0.55f)
	{
		// ÆøÅº 1°³ + ¿­¼è 1°³
		{
			BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
			TmpObject->SetType(BombType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.55f <= RandomFloat && RandomFloat < 0.6f)
	{
		// 5¿ø
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Black);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.65f)
	{
		// 3¿ø + ÆøÅº
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
			TmpObject->SetType(BombType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.65f <= RandomFloat && RandomFloat < 0.7f)
	{
		// 3¿ø + ¿­¼è
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.7f <= RandomFloat && RandomFloat < 0.75f)
	{
		// ¹èÅÍ¸®
		BatteryItem* TmpObject = GetLevel()->CreateActor<BatteryItem>();
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.75f <= RandomFloat && RandomFloat < 0.775f)
	{
		// ¸¶½ºÅÍÅ°
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Master);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.775f <= RandomFloat && RandomFloat < 0.8f)
	{
		// 5¿ø + ÆøÅº + ¿­¼è
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Black);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
			TmpObject->SetType(BombType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else
	{
		// 1¿ø + ¿­¼è
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
}

void BoxItem::GoldBoxReward()
{
	float RandomFloat = GameEngineRandom::MainRandom->RandomFloat(0.0f, 1.0f);
	if (0.0f <= RandomFloat && RandomFloat < 0.15f)
	{
		// 3¿ø + ÆøÅº
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
			TmpObject->SetType(BombType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.15f <= RandomFloat && RandomFloat < 0.3f)
	{
		// 3¿ø + ¿­¼è
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.3f <= RandomFloat && RandomFloat < 0.45f)
	{
		// 8¿ø
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Black);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.45f <= RandomFloat && RandomFloat < 0.5f)
	{
		// 2¿ø + ¿­¼è 2°³
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Two);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.5f <= RandomFloat && RandomFloat < 0.55f)
	{
		// ÆøÅº 2°³ + ¿­¼è 2°³
		{
			BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
			TmpObject->SetType(BombType::Two);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}

		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Two);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.55f <= RandomFloat && RandomFloat < 0.6f)
	{
		// 5¿ø
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Black);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.65f)
	{
		// 5¿ø + ÆøÅº2°³
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Black);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
			TmpObject->SetType(BombType::Two);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.65f <= RandomFloat && RandomFloat < 0.7f)
	{
	 // 5¿ø + ¿­¼è2°³
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Black);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Two);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.7f <= RandomFloat && RandomFloat < 0.75f)
	{
		// ¹èÅÍ¸®
		BatteryItem* TmpObject = GetLevel()->CreateActor<BatteryItem>();
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.75f <= RandomFloat && RandomFloat < 0.775f)
	{
		// ¸¶½ºÅÍÅ°
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Master);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.775f <= RandomFloat && RandomFloat < 0.8f)
	{
		// 5¿ø + ÆøÅº + ¿­¼è
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Black);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
			TmpObject->SetType(BombType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Normal);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else
	{
		// 10¿ø + ¿­¼è 2°³
		{
			MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
			TmpObject->SetType(MoneyType::Silver);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Two);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
}

