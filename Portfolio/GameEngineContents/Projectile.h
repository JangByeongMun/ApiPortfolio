#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

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
	inline void	SetSpeed(const float& _Value)
	{
		Speed_ = _Value;
	}

protected:

private:
	ProjectileType _Type;
	float4 Vec_;
	float Speed_;

	void Start() override;
	void Update() override;
};

