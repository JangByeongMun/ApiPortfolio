#include "Shooter.h"
#include <GameEngine/GameEngineLevel.h>

Shooter::Shooter() 
{
}

Shooter::~Shooter() 
{
}

void Shooter::Shoot(float4 _Vector, ProjectileType _Type, float4 _AddPivot, float _LifeTime, float _Damage)
{
	Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
	Ptr->SetPosition(GetPosition() + _AddPivot);
	Ptr->SetVector(_Vector);
	Ptr->SetLifeTime_(_LifeTime);
	Ptr->SetDamage(_Damage);
	Ptr->SetType(_Type);
}