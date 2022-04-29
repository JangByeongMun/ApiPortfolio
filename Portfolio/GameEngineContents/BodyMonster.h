#pragma once
#include "Monster.h"

enum class MoveDir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class BodyMonster : public Monster
{
public:
	// constrcuter destructer
	BodyMonster();
	~BodyMonster();

	// delete Function
	BodyMonster(const BodyMonster& _Other) = delete;
	BodyMonster(BodyMonster&& _Other) noexcept = delete;
	BodyMonster& operator=(const BodyMonster& _Other) = delete;
	BodyMonster& operator=(BodyMonster&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* BodyRenderer_;

	virtual void BodySetting();
	void BodyUpdate(float4 _Pos);
	MoveDir GetDir(float4 _Dir);
};

