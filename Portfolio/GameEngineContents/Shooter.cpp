#include "Shooter.h"
#include <GameEngine/GameEngineLevel.h>

Shooter::Shooter() 
{
}

Shooter::~Shooter() 
{
}

void Shooter::Shoot(float4 _Vector, ProjectileType _Type, float4 _AddPivot)
{
	Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
	Ptr->SetType(_Type);
	Ptr->SetPosition(GetPosition() + _AddPivot);
	Ptr->SetVector(_Vector);
}