#pragma once

// 설명 : 투사체가 막히는 벽
class Obstruction
{
public:
	// constrcuter destructer
	Obstruction();
	~Obstruction();

	// delete Function
	Obstruction(const Obstruction& _Other) = delete;
	Obstruction(Obstruction&& _Other) noexcept = delete;
	Obstruction& operator=(const Obstruction& _Other) = delete;
	Obstruction& operator=(Obstruction&& _Other) noexcept = delete;

protected:

private:

};

