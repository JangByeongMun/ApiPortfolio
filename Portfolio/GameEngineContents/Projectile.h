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
	inline void SetType(ProjectileType _Type)
	{
		Type_ = _Type;
	}

protected:

private:
	ProjectileType Type_;
	float4 Vec_;

	void Start() override;
	void Update() override;
};

