#include "DamageableActor.h"

DamageableActor::DamageableActor()
	: hp_(1)
	, isDeath_(false)
{
}

DamageableActor::~DamageableActor() 
{
}

void DamageableActor::Death(bool _isDeath)
{
	isDeath_ = _isDeath;
}

void DamageableActor::DamageTake(float _value)
{
	if (true == isDeath_)
	{
		return;
	}

	hp_ -= (_value);
	if (0 >= hp_)
	{
		hp_ = 0;
		
	}
}

