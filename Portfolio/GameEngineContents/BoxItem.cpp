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
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

BoxItem::BoxItem() 
	: Type_(BoxType::Normal)
	, AnimTimer_(0.0f)
	, IsOpen_(false)
	, IsSetting_(false)
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

	IsSetting_ = true;
}

void BoxItem::Start()
{
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_005_chests_Normal.bmp", static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Idle", 0, 0, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Open", 1, 1, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Appear", 6, 8, 0.1f, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Opening", 2, 4, 0.1f, false);
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_005_chests_Gold.bmp", static_cast<int>(ORDER::PLAYER));
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Idle", 0, 0, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Open", 1, 1, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Appear", 6, 8, 0.1f, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Opening", 2, 4, 0.1f, false);
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}

	{
		GameEngineSound::SoundPlayOneShotWithVolume("chest drop 1.wav", 0, 0.01f * Option_SFX);
	}
}

void BoxItem::Update()
{
	if (false == IsSetting_)
	{
		return;
	}

	// 오픈여부 상관없이 플레이어와 충돌했을때
	// 밀리도록 구현
	if (nullptr != Collision_ && true == Collision_->CollisionCheckRect("Player"))
	{
		float4 TmpDir = GetPosition() - Player::MainPlayer->GetPosition();
		TmpDir.Normal2D();
		AddDir(TmpDir * 2.0f);
	}
	SetObjectMove();

	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.3f)
	{
		switch (Type_)
		{
		case BoxType::Normal:
			RendererVector_[0]->ChangeAnimation("Idle");
			break;
		case BoxType::Gold:
			RendererVector_[1]->ChangeAnimation("Idle");
			break;
		default:
			break;
		}

		Collision_ = CreateCollision("Box", { 90, 60 });
	}

	if (false == IsOpen_) // 닫혀있을떄
	{
		// 박스가 플레이어랑 충돌했을때
		if (nullptr != Collision_ && true == Collision_->CollisionCheckRect("Player"))
		{
			{
				GameEngineSound::SoundPlayOneShotWithVolume("chest open 1.wav", 0, 0.01f * Option_SFX);
			}

			if (BoxType::Normal == Type_) // 노말박스면 그냥열림
			{
				IsOpen_ = true;
				AnimTimer_ = 0.0f;
				switch (Type_)
				{
				case BoxType::Normal:
					RendererVector_[0]->ChangeAnimation("Opening");
					break;
				case BoxType::Gold:
					RendererVector_[1]->ChangeAnimation("Opening");
					break;
				default:
					break;
				}
				NormalBoxReward();
			}
			else if (BoxType::Gold == Type_) // 황금박스면 키가 잇어야 열린다
			{
				if (true == Player::MainPlayer->HaveKey())
				{
					Player::MainPlayer->MinusItem(ItemType::Key, 1);
					IsOpen_ = true;
					AnimTimer_ = 0.0f;
					switch (Type_)
					{
					case BoxType::Normal:
						RendererVector_[0]->ChangeAnimation("Opening");
						break;
					case BoxType::Gold:
						RendererVector_[1]->ChangeAnimation("Opening");
						break;
					default:
						break;
					}
					GoldBoxReward();
				}
			}
		}
	}
	else // 열려있을때
	{
		AnimTimer_ += GameEngineTime::GetDeltaTime();
		if (AnimTimer_ >= 0.3f)
		{
			switch (Type_)
			{
			case BoxType::Normal:
				RendererVector_[0]->ChangeAnimation("Open");
				break;
			case BoxType::Gold:
				RendererVector_[1]->ChangeAnimation("Open");
				break;
			default:
				break;
			}
		}
	}
}

void BoxItem::NormalBoxReward()
{
	float RandomFloat = GameEngineRandom::MainRandom->RandomFloat(0.0f, 1.0f);
	if (0.0f <= RandomFloat && RandomFloat < 0.15f)
	{
		// 열쇠 1개
		KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
		TmpObject->SetType(KeyType::Normal);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.15f <= RandomFloat && RandomFloat < 0.3f)
	{
		// 폭탄 1개
		BombItem* TmpObject = GetLevel()->CreateActor<BombItem>();
		TmpObject->SetType(BombType::Normal);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.3f <= RandomFloat && RandomFloat < 0.45f)
	{
		// 3원
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
		// 열쇠 2개
		KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
		TmpObject->SetType(KeyType::Two);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.5f <= RandomFloat && RandomFloat < 0.55f)
	{
		// 폭탄 1개 + 열쇠 1개
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
		// 5원
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Black);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.65f)
	{
		// 3원 + 폭탄
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
		// 3원 + 열쇠
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
		// 배터리
		BatteryItem* TmpObject = GetLevel()->CreateActor<BatteryItem>();
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.75f <= RandomFloat && RandomFloat < 0.775f)
	{
		// 마스터키
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Master);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.775f <= RandomFloat && RandomFloat < 0.8f)
	{
		// 5원 + 폭탄 + 열쇠
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
		// 1원 + 열쇠
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
		// 3원 + 폭탄
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
		// 3원 + 열쇠
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
		// 8원
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
		// 2원 + 열쇠 2개
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
		// 폭탄 2개 + 열쇠 2개
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
		// 5원
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Black);
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.6f <= RandomFloat && RandomFloat < 0.65f)
	{
		// 5원 + 폭탄2개
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
	 // 5원 + 열쇠2개
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
		// 배터리
		BatteryItem* TmpObject = GetLevel()->CreateActor<BatteryItem>();
		TmpObject->SetPosition(GetPosition());
		TmpObject->AddRanomDir(-10, 10);
	}
	else if (0.75f <= RandomFloat && RandomFloat < 0.775f)
	{
		// 마스터키
		{
			KeyItem* TmpObject = GetLevel()->CreateActor<KeyItem>();
			TmpObject->SetType(KeyType::Master);
			TmpObject->SetPosition(GetPosition());
			TmpObject->AddRanomDir(-10, 10);
		}
	}
	else if (0.775f <= RandomFloat && RandomFloat < 0.8f)
	{
		// 5원 + 폭탄 + 열쇠
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
		// 10원 + 열쇠 2개
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

