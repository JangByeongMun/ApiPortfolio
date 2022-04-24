#pragma once
#include "Shooter.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>

// 설명 : 몬스터들 기본
class Player;
class RoomActor;
class Monster : public Shooter
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;
	
	inline void SetRoom(RoomActor& _Room)
	{
		Room_ = &_Room;
	}

protected:
	RoomActor* Room_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	bool IsLeft_;

	void Start() override;
	void Update() override;
	virtual void MonsterUpdate() {};
	inline void MonsterSetting(float _AttackDelay, float _MoveSpeed)
	{
		AttackDelay_ = _AttackDelay;
		MoveSpeed_ = _MoveSpeed;
	}

///////////////////////////////// 공격
protected:
	float AttackTimer_;
	float AttackDelay_;

public:
	float4 AttackNormalDir();
	inline void SetAttackDelay(float _Value)
	{
		AttackDelay_ = _Value;
	}

///////////////////////////////// 이동
protected:
	float MoveSpeed_;

public:
	void MonsterSetMove(float4 _Value);
	inline void SetMoveSpeed(float _Speed) 
	{
		MoveSpeed_ = _Speed;
	}

///////////////////////////////// 피격
protected:
	float HP_;

public:
	inline void SetHP(float _HP)
	{
		HP_ = _HP;
	}
	virtual void Damaged(float _Damage);
	void MakeRandomBlood(int _Min, int _Max);
	virtual void MonsterDeath();
};

