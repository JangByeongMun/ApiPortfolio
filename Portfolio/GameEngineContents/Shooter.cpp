#include "Shooter.h"
#include <GameEngine/GameEngineLevel.h>

Shooter::Shooter() 
{
}

Shooter::~Shooter() 
{
}

void Shooter::Shoot(ProjectileType _Type, float4 _vector)
{
	Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
	Ptr->SetPosition(GetPosition());
	Ptr->SetVector(float4::LEFT);
	Ptr->SetSpeed(200.0f);
}