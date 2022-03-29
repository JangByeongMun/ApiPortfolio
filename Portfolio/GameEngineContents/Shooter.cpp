#include "Shooter.h"
#include <GameEngine/GameEngineLevel.h>

Shooter::Shooter() 
{
}

Shooter::~Shooter() 
{
}

void Shooter::Shoot(ProjectileType _type, float4 _vector)
{
	Projectile* ptr = GetLevel()->CreateActor<Projectile>();
	ptr->SetPosition(GetPosition());
	ptr->SetVector(float4::Left);
	ptr->SetSpeed(200.0f);
}