#include "Projectile.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

Projectile::Projectile() 
	: Vec_{0, 0}
	, Speed_ (0)
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("tears.bmp", RenderPivot::CENTER, { 0, 0 });
	Renderer->SetIndex(5);

	Death(2.0f);
}

void Projectile::Update()
{
	SetMove(Vec_ * GameEngineTime::GetDeltaTime() * Speed_);
}

