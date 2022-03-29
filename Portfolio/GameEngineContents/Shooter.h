#pragma once
#include "Projectile.h"
#include <GameEngine/GameEngineActor.h>

// 설명 : 투사체를 발사 하는 스크립트
class Shooter : public GameEngineActor
{
public:
	// constrcuter destructer
	Shooter();
	~Shooter();

	// delete Function
	Shooter(const Shooter& _Other) = delete;
	Shooter(Shooter&& _Other) noexcept = delete;
	Shooter& operator=(const Shooter& _Other) = delete;
	Shooter& operator=(Shooter&& _Other) noexcept = delete;

	void Shoot(ProjectileType _type, float4 _vector);

protected:

private:

};

