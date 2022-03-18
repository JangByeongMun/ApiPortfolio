#pragma once

// Ό³Έν :
class Poop
{
public:
	// constrcuter destructer
	Poop();
	~Poop();

	// delete Function
	Poop(const Poop& _Other) = delete;
	Poop(Poop&& _Other) noexcept = delete;
	Poop& operator=(const Poop& _Other) = delete;
	Poop& operator=(Poop&& _Other) noexcept = delete;

protected:

private:

};

