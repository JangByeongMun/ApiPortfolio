#pragma once
#include "Projectile.h"

// ���� : ����ü�� �߻� �ϴ� ��ũ��Ʈ
class Shooter
{
public:
	// constrcuter destructer
	Shooter();
	~Shooter();

	// delete Function
	Shooter(const Shooter& _Other) = delete;
	Shooter(Shooter&& _Other) noexcept = delete;
	Shooter& operator=(const Shooter& _Other) = delete;
	Shooter& operator=(Shooter&& _Other) noexcept = delete;

	void Shoot(const Projectile& _projectile);

protected:

private:

};

