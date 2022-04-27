#include "ShopItem.h"
#include <GameEngine/GameEngineRenderer.h>

ShopItem::ShopItem()
	: Type_(ShopType::Default)
	, Collision_(nullptr)
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
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(1);
		TmpRenderer->SetPivot({-20, 20});
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(5);
		TmpRenderer->SetPivot({ 0, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("shop_001_bitfont.bmp");
		TmpRenderer->SetIndex(10);
		TmpRenderer->SetPivot({ 20, 20 });
		RendererVector_.push_back(TmpRenderer);
	}
		break;
	case ShopType::Bomb:
		break;
	case ShopType::Key:
		break;
	case ShopType::Heart:
		break;
	case ShopType::Max:
		break;
	default:
		break;
	}
}

void ShopItem::Update()
{
}

