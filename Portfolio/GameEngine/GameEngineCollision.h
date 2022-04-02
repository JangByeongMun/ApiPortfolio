#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <vector>

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
	inline float4 GetCollisionPos()
	{
		return GetActor()->GetPosition() + Pivot_;
	}
	inline GameEngineRect GetRect()
	{
		return GameEngineRect(GetActor()->GetPosition() + Pivot_, Scale_);
	}

	bool CollisionCheck(
		const std::string& _TargetGroup,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle
	);
	bool CollisionResult(
		const std::string& _TargetGroup,
		std::vector<GameEngineCollision*>& _ColResult,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle
	);

	void DebugRender();

protected:

private:
	float4 Pivot_;
	float4 Scale_;
};

