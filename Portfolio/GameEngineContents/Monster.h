#pragma once
#include "Shooter.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <vector>

// ���� : ���͵� �⺻
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
	inline RoomActor* GetRoom()
	{
		return Room_;
	}

protected:
	RoomActor* Room_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	bool IsLeft_;

	void Start() override;
	void Update() override;
	virtual void MonsterUpdate() {};
	virtual void MonsterDamaged() {};
	inline void MonsterSetting(float _AttackDelay, float _MoveSpeed)
	{
		AttackDelay_ = _AttackDelay;
		MoveSpeed_ = _MoveSpeed;
	}

///////////////////////////////// ����
protected:
	float AttackTimer_;
	float AttackDelay_;
	bool IsAttack_;

public:
	float4 AttackNormalDir();
	inline void SetAttackDelay(float _Value)
	{
		AttackDelay_ = _Value;
	}
	inline void SetAttack(bool _Attack)
	{
		IsAttack_ = _Attack;
	}

///////////////////////////////// �̵�
protected:
	float MoveSpeed_;

public:
	void MonsterSetMoveToFly(float4 _Value);
	void MonsterSetMoveToWalk(float4 _Value);
	bool MonsterSetMoveToTeleport(float4 _Value);
	bool MonsterSetMoveToFlyReturn(float4 _Value);
	bool MonsterSetMoveToWalkReturn(float4 _Value);

	inline void SetMoveSpeed(float _Speed)
	{
		MoveSpeed_ = _Speed;
	}

///////////////////////////////// �ǰ�
protected:
	float HP_;
	float MaxHP_;
	bool IsInvincibility_; // ����

public:
	inline void SetHP(float _HP)
	{
		MaxHP_ = _HP;
		HP_ = _HP;
	}
	inline float GetHP()
	{
		return HP_;
	}
	virtual void Damaged(float _Damage);
	virtual void Heal(float _Value);
	void MakeRandomBlood(int _Min, int _Max);
	virtual void MonsterDeath();
};

