#include "ShopKeeper.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

ShopKeeper::ShopKeeper() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, IsDead_(false)
{
}

ShopKeeper::~ShopKeeper() 
{
}

void ShopKeeper::DeadAnim()
{
	if (true == IsDead_)
	{
		return;
	}

	IsDead_ = true;
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 2);
	Renderer_->ChangeAnimation("Dead" + std::to_string(RandomInt));
}

void ShopKeeper::Start()
{
	Collision_ = CreateCollision("ShopKeeper", { 50, 50 });
	Renderer_ = CreateRenderer("effect_000_shopkeepers.bmp");
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper1", 0, 0, 0, false);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper2", 1, 2, 0.1f, true);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper3", 3, 3, 0, false);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper4", 4, 5, 0.1f, true);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper5", 6, 7, 0.1f, true);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper6", 8, 8, 0, false);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper7", 9, 9, 0, false);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper8", 10, 10, 0, false);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Keeper9", 11, 11, 0, false);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Dead1", 12, 12, 0, false);
	Renderer_->CreateAnimation("effect_000_shopkeepers.bmp", "Dead2", 13, 13, 0, false);

	int RandomInt = GameEngineRandom::MainRandom->RandomInt(1, 9);
	Renderer_->ChangeAnimation("Keeper" + std::to_string(RandomInt));
}
