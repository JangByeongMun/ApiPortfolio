#pragma once
#include "Monster.h"

enum class FlyType
{
	Normal,
	Red,
};

// Ό³Έν :
class Fly : public Monster
{
public:
	// constrcuter destructer
	Fly();
	~Fly();

	// delete Function
	Fly(const Fly& _Other) = delete;
	Fly(Fly&& _Other) noexcept = delete;
	Fly& operator=(const Fly& _Other) = delete;
	Fly& operator=(Fly&& _Other) noexcept = delete;

	void SetType(FlyType _Type);

protected:

private:
	FlyType Type_;
	GameEngineRenderer* DeadRenderer_;

	void Start() override;
	void MonsterUpdate() override;
	void MonsterDeath() override;
};

