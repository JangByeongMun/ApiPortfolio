#pragma once

// Ό³Έν :
class PoopRed
{
public:
	// constrcuter destructer
	PoopRed();
	~PoopRed();

	// delete Function
	PoopRed(const PoopRed& _Other) = delete;
	PoopRed(PoopRed&& _Other) noexcept = delete;
	PoopRed& operator=(const PoopRed& _Other) = delete;
	PoopRed& operator=(PoopRed&& _Other) noexcept = delete;

protected:

private:

};

