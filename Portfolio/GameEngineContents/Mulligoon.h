#pragma once
#include "Monster.h"

// Ό³Έν :
class Mulligoon : public Monster
{
public:
	// constrcuter destructer
	Mulligoon();
	~Mulligoon();

	// delete Function
	Mulligoon(const Mulligoon& _Other) = delete;
	Mulligoon(Mulligoon&& _Other) noexcept = delete;
	Mulligoon& operator=(const Mulligoon& _Other) = delete;
	Mulligoon& operator=(Mulligoon&& _Other) noexcept = delete;

protected:

private:

	void Start() override;
};

