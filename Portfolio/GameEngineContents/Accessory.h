#pragma once

// Ό³Έν :
class Accessory
{
public:
	// constrcuter destructer
	Accessory();
	~Accessory();

	// delete Function
	Accessory(const Accessory& _Other) = delete;
	Accessory(Accessory&& _Other) noexcept = delete;
	Accessory& operator=(const Accessory& _Other) = delete;
	Accessory& operator=(Accessory&& _Other) noexcept = delete;

protected:

private:

};

