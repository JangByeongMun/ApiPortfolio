#include "Poop.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineCollision.h>
#include "HeartItem.h"
#include "MoneyItem.h"
#include "ContentsEnum.h"

Poop::Poop() 
	: CurrentHP_(10)
	, Collision_(nullptr)
	, Renderer_(nullptr)
{
}

Poop::~Poop() 
{
}

void Poop::Start()
{
	Collision_ = CreateCollision("Poop", {60, 60});
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 4);
	Renderer_ = CreateRenderer("grid_poop_" + std::to_string(RandomInt) + ".bmp", static_cast<int>(ORDER::PLAYER));
	Renderer_->SetIndex(0);
}

void Poop::RandomDrop()
{
	float RandomFloat = GameEngineRandom::MainRandom->RandomFloat(0.0f, 1.0f);
	if (0.0f <= RandomFloat && RandomFloat < 0.2f)
	{
		HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
		TmpHeart->SetPosition(GetPosition());
		TmpHeart->Setting(HeartType::RedHalf);
	}
	else if (0.2f <= RandomFloat && RandomFloat < 0.4f)
	{
		HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
		TmpHeart->SetPosition(GetPosition());
		TmpHeart->Setting(HeartType::Red);
	}
	else if (0.4f <= RandomFloat && RandomFloat < 0.6f)
	{
		MoneyItem* TmpObject = GetLevel()->CreateActor<MoneyItem>();
		TmpObject->SetType(MoneyType::Normal);
		TmpObject->SetPosition(GetPosition());
	}
}

void Poop::AddHp(float _Value)
{
	CurrentHP_ += _Value;
	if (CurrentHP_ <= 0.0f)
	{
		CurrentHP_ = 0.0f;
		Collision_->Off();
		Renderer_->SetOrder(static_cast<int>(ORDER::BACKGROUND));
		RandomDrop();
	}

	if (CurrentHP_ >= 8.0f)
	{
		Renderer_->SetIndex(0);
	}
	else if (CurrentHP_ >= 6.0f)
	{
		Renderer_->SetIndex(1);
	}
	else if (CurrentHP_ >= 4.0f)
	{
		Renderer_->SetIndex(2);
	}
	else if (CurrentHP_ >= 2.0f)
	{
		Renderer_->SetIndex(3);
	}
	else if (CurrentHP_ >= 0.0f)
	{
		Renderer_->SetIndex(4);
	}
}

