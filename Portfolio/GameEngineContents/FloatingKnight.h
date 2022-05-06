#pragma once
#include "Monster.h"

// Ό³Έν :
class FloatingKnight : public Monster
{
public:
	// constrcuter destructer
	FloatingKnight();
	~FloatingKnight();

	// delete Function
	FloatingKnight(const FloatingKnight& _Other) = delete;
	FloatingKnight(FloatingKnight&& _Other) noexcept = delete;
	FloatingKnight& operator=(const FloatingKnight& _Other) = delete;
	FloatingKnight& operator=(FloatingKnight&& _Other) noexcept = delete;

protected:

private:
	std::vector<GameEngineCollision*> CollisionVector_;
	bool IsAttack_;
	float4 MoveDir_;
	
	void Start() override;
	void MonsterUpdate() override;
	void ChangeCollision(int _Index);
};

