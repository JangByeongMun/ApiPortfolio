#pragma once
#include "ContentsEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

// 설명 : 투사체
class Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	Projectile();
	~Projectile();

	// delete Function
	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	inline void SetVector(const float4& _Value)
	{
		Vec_ = _Value;
	}
	inline void SetType(ProjectileType _Type)
	{
		Type_ = _Type;
	}
	inline void SetLifeTime_(float _Value)
	{
		Lifetime_ = _Value;
		CurrentTimer_ = 0.0f;
		Death(Lifetime_);
	}

protected:

private:
	GameEngineCollision* Collision_;
	ProjectileType Type_;
	float4 Vec_;
	float Lifetime_;
	float CurrentTimer_;

	void Start() override;
	void Update() override;
};

