#pragma once
#include "Monster.h"

enum class BoomFlyType
{
	Normal,
	Red,
};

// Ό³Έν :
class BoomFly : public Monster
{
public:
	// constrcuter destructer
	BoomFly();
	~BoomFly();

	// delete Function
	BoomFly(const BoomFly& _Other) = delete;
	BoomFly(BoomFly&& _Other) noexcept = delete;
	BoomFly& operator=(const BoomFly& _Other) = delete;
	BoomFly& operator=(BoomFly&& _Other) noexcept = delete;

	void Setting(BoomFlyType _Type);

protected:

private:
	BoomFlyType Type_;
	float4 MoveDir_;

	void MonsterUpdate() override;
	void MonsterDeath() override;
	void MoveZigZag(float4 _Value);
	void Boom();
};

