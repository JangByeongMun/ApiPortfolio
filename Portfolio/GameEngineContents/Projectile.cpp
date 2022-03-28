#include "Projectile.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Projectile::Projectile() 
	: vec_{0, 0}
	, speed_ (0)
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	GameEngineRenderer* renderer = CreateRenderer("tears.bmp", RenderPivot::CENTER, { 0, 0 });
	renderer->SetIndex(5);

	Death(2.0f);
}

void Projectile::Update()
{
	SetMove(vec_ * GameEngineTime::GetDeltaTime() * speed_);
}

