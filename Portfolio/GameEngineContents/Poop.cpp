#include "Poop.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineCollision.h>

Poop::Poop() 
	: CurrentHP_(10)
{
}

Poop::~Poop() 
{
}

void Poop::Start()
{
	Collision_ = CreateCollision("Poop", {60, 60});
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 4);
	Renderer_ = CreateRenderer("grid_poop_" + std::to_string(RandomInt) + ".bmp");
	Renderer_->SetIndex(0);
}

void Poop::AddHp(float _Value)
{
	CurrentHP_ += _Value;
	if (CurrentHP_ <= 0.0f)
	{
		CurrentHP_ = 0.0f;
		Collision_->Off();
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

