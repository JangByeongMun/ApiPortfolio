#include "PassiveItem.h"
#include <GameEngineBase/GameEngineTime.h>
#include "Player.h"

PassiveItem::PassiveItem()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, Type_(PassiveType::Default)
{
}

PassiveItem::~PassiveItem() 
{
}

void PassiveItem::Setting(PassiveType _Type)
{
	Type_ = _Type;

	{
	 	GameEngineRenderer* Renderer = CreateRenderer("levelitem_001_itemaltar.bmp");
		Renderer->SetPivot({0, 20});
	}

	Renderer_ = CreateRenderer(ItemNameVector_[static_cast<int>(Type_)]);
	Collision_ = CreateCollision("Passive", { 50, 50 });
}

void PassiveItem::Start()
{
	ItemNameVector_.push_back("None.bmp");
	ItemNameVector_.push_back("collectibles_001.bmp");
}

void PassiveItem::Update()
{
	// 플레이어와 충돌
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->AddPassive(Type_);
		Death();
	}

	// 애니메이션 
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ <= 0.5f)
	{
		float4 LerpFloat4 = float4::Lerp({ 0, -35 }, { 0, -45 }, AnimTimer_ * 2);
		Renderer_->SetPivot(LerpFloat4);
	}
	else if (AnimTimer_ <= 1.0f)
	{
		float4 LerpFloat4 = float4::Lerp({ 0, -45 }, {0, -35}, (AnimTimer_-0.5f) * 2);
		Renderer_->SetPivot(LerpFloat4);
	}
	else
	{
		AnimTimer_ = 0.0f;
	}
}

