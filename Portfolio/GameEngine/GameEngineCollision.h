#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <vector>

// ���� :
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;

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

	inline bool CollisionCheckRect(const std::string& _TargetGroup)
	{
		return CollisionCheck(_TargetGroup, CollisionType::Rect, CollisionType::Rect);
	}
	bool CollisionCheck(
		const std::string& _TargetGroup,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle
	);

	inline bool CollisionResultRect(const std::string& _TargetGroup, std::vector<GameEngineCollision*>& _ColResult)
	{
		return CollisionResult(_TargetGroup, _ColResult, CollisionType::Rect, CollisionType::Rect);
	}
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

	std::string CollisionName_;
};

