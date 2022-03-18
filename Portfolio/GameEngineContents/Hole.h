#pragma once

// Ό³Έν :
class Hole
{
public:
	// constrcuter destructer
	Hole();
	~Hole();

	// delete Function
	Hole(const Hole& _Other) = delete;
	Hole(Hole&& _Other) noexcept = delete;
	Hole& operator=(const Hole& _Other) = delete;
	Hole& operator=(Hole&& _Other) noexcept = delete;

protected:

private:

};

