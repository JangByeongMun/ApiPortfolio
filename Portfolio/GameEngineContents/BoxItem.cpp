#include "BoxItem.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

BoxItem::BoxItem() 
	: Collision_(nullptr)
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
		break;
	case BoxType::Gold:
		RendererVector_[1]->On();
		RendererVector_[1]->ChangeAnimation("Appear");
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
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Appear", 6, 8, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Normal.bmp", "Opening", 2, 4, 0, false);
		TmpRenderer->ChangeAnimation("Idle");
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}
	{
		GameEngineRenderer* TmpRenderer = CreateRenderer("pickup_005_chests_Gold.bmp");
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Idle", 0, 0, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Open", 1, 1, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Appear", 6, 8, 0, false);
		TmpRenderer->CreateAnimation("pickup_005_chests_Gold.bmp", "Opening", 2, 4, 0, false);
		TmpRenderer->ChangeAnimation("Idle");
		TmpRenderer->Off();
		RendererVector_.push_back(TmpRenderer);
	}

	Collision_ = CreateCollision("Box", {90, 60});
}

void BoxItem::Update()
{
}

