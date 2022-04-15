#include "Projectile.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Projectile::Projectile() 
	: Collision_()
	, Type_(ProjectileType::PLAYER_BASIC)
	, Vec_({ 0, 0 })
	, Lifetime_(0)
	, CurrentTimer_(0)
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("tears.bmp", RenderPivot::CENTER, { 0, 0 });
	Renderer->SetIndex(5);
	
	Collision_ = CreateCollision("Projectile", { 30, 30 }, { 0, 0 });
}

void Projectile::Update()
{
	CurrentTimer_ += GameEngineTime::GetDeltaTime();


	if (Lifetime_ - CurrentTimer_ <= 0.3f)
	{
		Vec_ += {0, 600 * GameEngineTime::GetDeltaTime()};
	}

	SetMove(Vec_ * GameEngineTime::GetDeltaTime());
}

