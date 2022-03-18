#pragma once

// Ό³Έν :
class StoneBlack
{
public:
	// constrcuter destructer
	StoneBlack();
	~StoneBlack();

	// delete Function
	StoneBlack(const StoneBlack& _Other) = delete;
	StoneBlack(StoneBlack&& _Other) noexcept = delete;
	StoneBlack& operator=(const StoneBlack& _Other) = delete;
	StoneBlack& operator=(StoneBlack&& _Other) noexcept = delete;

protected:

private:

};

