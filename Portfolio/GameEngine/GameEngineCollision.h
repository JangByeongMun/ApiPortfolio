#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"

// Ό³Έν :
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	inline void SetPivot(const float4& _Pivot)
	{
		Pivot_ = _Pivot;
	}
	inline void SetScale(const float4& _Scale)
	{
		Scale_ = _Scale;
	}

	bool CollisionCheck(
		const std::string& _TargetGroup,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Tartget = CollisionType::Circle
	);

protected:

private:
	float4 Pivot_;
	float4 Scale_;
};

