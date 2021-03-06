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

		int AddValue = 5;
		if (false == IsPlayerProjectile() && Type_ == ProjectileType::ENEMY_BASIC)
		{
			AddValue += 16;
		}
		if (Type_ == ProjectileType::ENEMY_IPECAC)
		{
			AddValue += 3;
		}

		if (2.0f <= Damage_ && Damage_ < 3.0f)
		{
			AddValue -= 1;
		}
		else if (4.0f <= Damage_ && Damage_ < 5.0f)
		{
			AddValue += 1;
		}
		else if (5.0f <= Damage_ && Damage_ < 6.0f)
		{
			AddValue += 2;
		}
		else if (6.0f <= Damage_ && Damage_ < 7.0f)
		{
			AddValue += 3;
		}
		else if (7.0f <= Damage_ && Damage_ < 8.0f)
		{
			AddValue += 4;
		}
		else if (8.0f <= Damage_)
		{
			AddValue += 5;
		}

		std::string TmpName = "";
		switch (Type_)
		{
		case ProjectileType::PLAYER_BASIC:
			TmpName = "tears.bmp";
			break;
		case ProjectileType::ENEMY_BASIC:
			TmpName = "tears.bmp";
			break;
		case ProjectileType::ENEMY_IPECAC:
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer("shadow.bmp", RenderPivot::CENTER, { 0, 0 }, static_cast<int>(ORDER::BACKPLAYER));
			TmpRenderer->SetScale({ 40, 20 });
			TmpRenderer->SetAlpha(100);
		}
			TmpName = "tears2.bmp";
			break;
		default:
			break;
		}
		Renderer_ = CreateRenderer(TmpName, RenderPivot::CENTER, { 0, 0 }, static_cast<int>(ORDER::PLAYER));
		Renderer_->SetIndex(AddValue);
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
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	ProjectileType Type_;
	float4 Vec_;
	float Lifetime_;
	float CurrentTimer_;
	float Damage_;

	void Start() override;
	void Update() override;

};

