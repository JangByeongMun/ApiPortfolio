#include "Projectile.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Projectile::Projectile() 
	: Collision_()
	, Type_(ProjectileType::PLAYER_BASIC)
	, Vec_({ 0, 0 })
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("tears.bmp", RenderPivot::CENTER, { 0, 0 });
	Renderer->SetIndex(5);
	
	Collision_ = CreateCollision("Projectile", { 96, 96 }, { 0, 0 });

	Death(2.0f);
}

void Projectile::Update()
{
	SetMove(Vec_ * GameEngineTime::GetDeltaTime());
}

