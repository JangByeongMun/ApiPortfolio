#pragma once
#include "Projectile.h"
#include <GameEngine/GameEngineActor.h>

// ���� : ����ü�� �߻� �ϴ� ��ũ��Ʈ
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

