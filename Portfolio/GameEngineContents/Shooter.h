#pragma once
#include "Projectile.h"
#include <GameEngine/GameEngineActor.h>

// ���� : ����ü�� �߻� �ϴ� ��ũ��Ʈ
class Shooter : public GameEngineActor
{
public:
	// constrcuter destructer
	Shooter();
	virtual ~Shooter();

	// delete Function
	Shooter(const Shooter& _Other) = delete;
	Shooter(Shooter&& _Other) noexcept = delete;
	Shooter& operator=(const Shooter& _Other) = delete;
	Shooter& operator=(Shooter&& _Other) noexcept = delete;

	void Shoot(float4 _Vector, ProjectileType _Type = ProjectileType::PLAYER_BASIC, float4 _AddPivot = { 0, 0 }, float _LifeTime = 1.0f);

private:

};

