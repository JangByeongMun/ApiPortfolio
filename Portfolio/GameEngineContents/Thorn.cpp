#include "Thorn.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "PlayerHP.h"

Thorn::Thorn()
	: Renderer_(nullptr)
	, ShadowRenderer_(nullptr)
	, Collision_(nullptr)
	, Type_(ThornType::Default)
{
}

Thorn::~Thorn() 
{
}

void Thorn::SetType(ThornType _Type)
{
	Type_ = _Type;
	Renderer_ = CreateRenderer("grid_spikes.bmp");
	ShadowRenderer_ = CreateRenderer("grid_spikes_Shadow.bmp");
	ShadowRenderer_->SetAlpha(100);
	Collision_ = CreateCollision("Thron", {50, 50});

	switch (Type_)
	{
	case ThornType::Always:
	{
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 3);
		Renderer_->SetIndex(RandomInt * 4);
		ShadowRenderer_->SetIndex(RandomInt * 4);
		break;
	}
	case ThornType::Anim:
	{
		break;
	}
	default:
		break;
	}
}

void Thorn::Update()
{
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->GetPlayerHP()->MinusHearts(true);
	}
}