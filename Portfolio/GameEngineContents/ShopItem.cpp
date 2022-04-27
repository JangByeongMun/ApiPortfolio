#include "ShopItem.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "Player.h"
#include "PassiveItem.h"
#include "PlayerHP.h"

ShopItem::ShopItem()
	: Type_(ShopType::Default)
	, Collision_(nullptr)
	, Price_ (0)
{
}

ShopItem::~ShopItem()
{
}

void ShopItem::SetType(ShopType _Type)
{
	Type_ = _Type;
	Collision_ = CreateCollision("ShopItem", { 50, 50 });
	
	switch (Type_)
	{
	case ShopType::Default:
		break;
	case ShopType::Passive:
	{
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, PassiveItem::ItemNameVector_.size() - 1);
		std::string TmpName = PassiveItem::ItemNameVector_[RandomInt];
		PassiveType_ = static_cast<PassiveType>(RandomInt);
		GameEngineRenderer* TmpRenderer = CreateRenderer(TmpName);
		TmpRenderer->SetPivot({ 0, -40 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(1);
		TmpRenderer->SetPivot({-20, 20});
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(5);
		TmpRenderer->SetPivot({ 5, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(10);
		TmpRenderer->SetPivot({ 30, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	Price_ = 15;
		break;
	case ShopType::Bomb:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_016_bomb.bmp");
		TmpRenderer->SetIndex(0);
		TmpRenderer->SetPivot({ 0, -40 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(5);
		TmpRenderer->SetPivot({ -10, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(10);
		TmpRenderer->SetPivot({ 15, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	Price_ = 5;
		break;
	case ShopType::Key:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_003_key.bmp");
		TmpRenderer->SetIndex(0);
		TmpRenderer->SetPivot({ 0, -40 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(5);
		TmpRenderer->SetPivot({ -10, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(10);
		TmpRenderer->SetPivot({ 15, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	Price_ = 5;
	break;
	case ShopType::Heart:
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_001_heart.bmp");
		TmpRenderer->SetIndex(0);
		TmpRenderer->SetPivot({ 0, -40 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(3);
		TmpRenderer->SetPivot({ -10, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(10);
		TmpRenderer->SetPivot({ 15, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	Price_ = 3;
	break;
	case ShopType::Max:
		break;
	default:
		break;
	}
}

void ShopItem::Update()
{
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		if (Player::MainPlayer->GetMoney() >= Price_)
		{
			switch (Type_)
			{
			case ShopType::Passive:
				Player::MainPlayer->AddPassive(PassiveType_);
				break;
			case ShopType::Bomb:
				Player::MainPlayer->AddItem(ItemType::Bomb);
				break;
			case ShopType::Key:
				Player::MainPlayer->AddItem(ItemType::Key);
				break;
			case ShopType::Heart:
				if (false == Player::MainPlayer->GetPlayerHP()->IsFullRed())
				{
					Player::MainPlayer->GetPlayerHP()->AddRedHp(1);
				}
				else
				{
					return;
				}
				break;
			default:
				MsgBoxAssert("세팅안된 아이템을 샀습니다.");
				break;
			}

			Player::MainPlayer->MinusItem(ItemType::Money, Price_);
			Off();
		}
	}
}

