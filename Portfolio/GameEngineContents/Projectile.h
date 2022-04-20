#pragma once
#include "ContentsEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
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


		GameEngineRenderer* Renderer = CreateRenderer("tears.bmp", RenderPivot::CENTER, { 0, 0 });
		Renderer->SetIndex(5);
	}
	inline void SetLifeTime_(float _Value)
	{
		Lifetime_ = _Value;
		CurrentTimer_ = 0.0f;
	}
	inline void SetDamage(float _Damage)
	{
		Damage_ = _Damage;
	}
	void DestroyProjectile();
	inline bool IsPlayerProjectile()
	{
		if (static_cast<int>(Type_) < static_cast<int>(ProjectileType::ENEMY_BASIC))
		{
			return true;
		}

		return false;
	}

protected:

private:
	GameEngineCollision* Collision_;
	ProjectileType Type_;
	float4 Vec_;
	float Lifetime_;
	float CurrentTimer_;
	float Damage_;

	void Start() override;
	void Update() override;

};

