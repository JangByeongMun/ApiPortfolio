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
	: Renderer_(nullptr)
	, Type_(BoxType::Normal)
	, AnimTimer_(0.0f)
	, IsOpen_(false)
	, IsSetting_(false)
	, State_(BoxState::Default)
{
}

BoxItem::~BoxItem()
{
}

void BoxItem::SetType(BoxType _Type)
{
	Type_ = _Type;

	std::string TmpName = "";
	switch (Type_)
	{
	case BoxType::Normal:
		TmpName = "pickup_005_chests_Normal.bmp";
		break;
	case BoxType::Gold:
		TmpName = "pickup_005_chests_Gold.bmp";
		break;
	default:
		break;
	}

	Renderer_->CreateAnimation(TmpName, "Idle", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation(TmpName, "Open", 1, 1, 0, false);
	Renderer_->CreateAnimation(TmpName, "Appear", 6, 8, 0.1f, false);
	Renderer_->CreateAnimation(TmpName, "Opening", 2, 4, 0.1f, false);
	Renderer_->ChangeAnimation("Idle");

	GameEngineSound::SoundPlayOneShotWithVolume("chest drop 1.wav", 0, 0.5f * Option_SFX);

	ChangeState(BoxState::Appear);
}

void BoxItem::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
}

void BoxItem::Update()
{
	StateUpdate();

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

void BoxItem::ChangeState(BoxState _State)
{
	if (State_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case BoxState::Appear:
		AppearStart();
		break;
	case BoxState::Idle:
		IdleStart();
		break;
	case BoxState::Open:
		OpenStart();
		break;
	default:
		break;
	}
	State_ = _State;
}

void BoxItem::StateUpdate()
{
	switch (State_)
	{
	case BoxState::Appear:
		AppearUpdate();
		break;
	case BoxState::Idle:
		IdleUpdate();
		break;
	case BoxState::Open:
		OpenUpdate();
		break;
	default:
		break;
	}
}

void BoxItem::AppearStart()
{
	AnimTimer_ = 0.0f;
	Renderer_->ChangeAnimation("Appear");
}

void BoxItem::IdleStart()
{
	Renderer_->ChangeAnimation("Idle");
}

void BoxItem::OpenStart()
{
	IsOpen_ = true;
	AnimTimer_ = 0.0f;
	Renderer_->ChangeAnimation("Opening");
	GameEngineSound::SoundPlayOneShotWithVolume("chest open 1.wav", 0, 0.5f * Option_SFX);
}

void BoxItem::AppearUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.3f)
	{
		Collision_ = CreateCollision("Box", { 90, 60 });
		ChangeState(BoxState::Idle);
	}
}

void BoxItem::IdleUpdate()
{
	if (false == IsOpen_) // ����������
	{
		// �ڽ��� �÷��̾�� �浹������
		if (nullptr != Collision_ && true == Collision_->CollisionCheckRect("Player"))
		{
			if (BoxType::Normal == Type_) // �븻�ڽ��� �׳ɿ���
			{
				NormalBoxReward();
				ChangeState(BoxState::Open);
			}
			else if (BoxType::Gold == Type_) // Ȳ�ݹڽ��� Ű�� �վ�� ������
			{
				if (true == Player::MainPlayer->HaveKey())
				{
					Player::MainPlayer->MinusItem(ItemType::Key, 1);
					GoldBoxReward();
					ChangeState(BoxState::Open);
				}
			}
		}
	}
}

void BoxItem::OpenUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.3f)
	{
		Renderer_->ChangeAnimation("Open");
	}
}

