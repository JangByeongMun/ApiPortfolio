#include "DamageableActor.h"

DamageableActor::DamageableActor()
	: HP_(1)
	, IsDeath_(false)
{
}

DamageableActor::~DamageableActor() 
{
}

void DamageableActor::Death(bool _IsDeath)
{
	IsDeath_ = _IsDeath;
}

void DamageableActor::DamageTake(float _Value)
{
	if (true == IsDeath_)
	{
		return;
	}

	HP_ -= (_Value);
	if (0 >= HP_)
	{
		HP_ = 0;
		
	}
}

