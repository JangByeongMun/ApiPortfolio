#include "BoxItem.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include "Player.h"

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

	Collision_ = CreateCollision("Box", {90, 60});
}

void BoxItem::Update()
{
	if (false == IsOpen_)
	{
		AnimTimer_ += GameEngineTime::GetDeltaTime();
		if (AnimTimer_ >= 0.3f)
		{
			for (int i = 0; i < RendererVector_.size(); i++)
			{
				RendererVector_[i]->ChangeAnimation("Idle");
			}
		}

		if (true == Collision_->CollisionCheckRect("Player"))
		{
			IsOpen_ = true;
			AnimTimer_ = 0.0f;
			for (int i = 0; i < RendererVector_.size(); i++)
			{
				RendererVector_[i]->ChangeAnimation("Opening");
			}

			switch (Type_)
			{
			case BoxType::Normal:
				NormalBoxReward();
				break;
			case BoxType::Gold:
				GoldBoxReward();
				break;
			default:
				break;
			}
		}
	}
	else
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

	if (true == Collision_->CollisionCheckRect("Player"))
	{
		float4 TmpDir = GetPosition() - Player::MainPlayer->GetPosition();
		TmpDir.Normal2D();
		AddDir(TmpDir * 100.0f * GameEngineTime::GetDeltaTime());
	}
	SetObjectMove();
}

void BoxItem::NormalBoxReward()
{

}

void BoxItem::GoldBoxReward()
{

}

