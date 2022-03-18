#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� : �������� ������ �ְ� ���ִ� Ŭ����
class DamageableActor : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageableActor();
	~DamageableActor();

	// delete Function
	DamageableActor(const DamageableActor& _Other) = delete;
	DamageableActor(DamageableActor&& _Other) noexcept = delete;
	DamageableActor& operator=(const DamageableActor& _Other) = delete;
	DamageableActor& operator=(DamageableActor&& _Other) noexcept = delete;

	virtual void Death(bool _isDeath);

protected:
	virtual void DamageTake(float _value);

private:
	float hp_;
	bool isDeath_;
};

