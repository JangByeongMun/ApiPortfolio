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
	if (false == IsOpen_) // ����������
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

		// �ڽ��� �÷��̾�� �浹������
		if (nullptr != Collision_ && true == Collision_->CollisionCheckRect("Player")) 
		{
			if (BoxType::Normal == Type_) // �븻�ڽ��� �׳ɿ���
			{
				IsOpen_ = true;
				AnimTimer_ = 0.0f;
				for (int i = 0; i < RendererVector_.size(); i++)
				{
					RendererVector_[i]->ChangeAnimation("Opening");
				}
				NormalBoxReward();
			}
			else if (BoxType::Gold == Type_) // Ȳ�ݹڽ��� Ű�� �վ�� ������
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
	else // ����������
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

	// ���¿��� ������� �÷��̾�� �浹������
	// �и����� ����
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
		// ���� 1��
		KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
		TmpObject->SetType(KeyType::Normal);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.15f <= RandomFloat && RandomFloat < 0.3f)
	{
		// ��ź 1��
		BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
		TmpObject->SetType(BombType::Normal);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.3f <= RandomFloat && RandomFloat < 0.45f)
	{
		// 3��
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
		// ���� 2��
		KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
		TmpObject->SetType(KeyType::Two);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.5f <= RandomFloat && RandomFloat < 0.55f)
	{
		// ��ź 1�� + ���� 1��
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
		// 5��
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Black);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.65f)
	{
		// 3�� + ��ź
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
		// 3�� + ����
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
		// ���͸�
		BatteryItem* TmpObject = GetLevel()->CreateActor<BatteryItem>();
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.75f <= RandomFloat && RandomFloat < 0.775f)
	{
		// ������Ű
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Master);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.775f <= RandomFloat && RandomFloat < 0.8f)
	{
		// 5�� + ��ź + ����
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
		// 1�� + ����
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
		// 3�� + ��ź
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
		// 3�� + ����
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
		// 8��
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
		// 2�� + ���� 2��
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
		// ��ź 2�� + ���� 2��
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
		// 5��
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Black);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.65f)
	{
		// 5�� + ��ź2��
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
	 // 5�� + ����2��
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
		// ���͸�
		BatteryItem* TmpObject = GetLevel()->CreateActor<BatteryItem>();
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.75f <= RandomFloat && RandomFloat < 0.775f)
	{
		// ������Ű
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Master);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.775f <= RandomFloat && RandomFloat < 0.8f)
	{
		// 5�� + ��ź + ����
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
		// 10�� + ���� 2��
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

