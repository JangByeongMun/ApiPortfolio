#include "Fire.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"
#include "PlayerHP.h"

Fire::Fire() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, FireHp_(10.0f)
{
}

Fire::~Fire() 
{
}

void Fire::Start()
{
	{
		GameEngineRenderer* Renderer = CreateRenderer(RenderPivot::CENTER);
		Renderer->CreateAnimation("grid_fireplace.bmp", "grid_fireplace_Off", 0, 0, 0, false);
		Renderer->CreateAnimation("grid_fireplace.bmp", "grid_fireplace_On", 1, 3, 0.1f, true);
		Renderer->ChangeAnimation("grid_fireplace_On");
		Renderer->SetPivot({ 0, 40 });

		FirePlaceRenderer_.push_back(Renderer);
	}

	{
		GameEngineRenderer* Renderer = CreateRenderer(RenderPivot::CENTER);
		Renderer->CreateAnimation("grid_fireplace_Shadow.bmp", "grid_fireplace_Off", 0, 0, 0, false);
		Renderer->CreateAnimation("grid_fireplace_Shadow.bmp", "grid_fireplace_On", 1, 3, 0.1f, true);
		Renderer->ChangeAnimation("grid_fireplace_On");
		Renderer->SetPivot({ 0, 40 });
		Renderer->SetAlpha(100);

		FirePlaceRenderer_.push_back(Renderer);
	}

	Renderer_ = CreateRenderer(static_cast<int>(ORDER::UI), RenderPivot::CENTER);
	Renderer_->CreateAnimation("effect_005_fire.bmp", "effect_005_fire", 0, 5, 0.1f, true);
	Renderer_->ChangeAnimation("effect_005_fire");
	Renderer_->SetAlpha(150);

	Collision_ = CreateCollision("Fire", {60, 65});
}

void Fire::Update()
{
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->GetPlayerHP()->AddRedHp(-1, true);
	}
}

