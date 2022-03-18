#pragma once

// Ό³Έν :
class FireRed
{
public:
	// constrcuter destructer
	FireRed();
	~FireRed();

	// delete Function
	FireRed(const FireRed& _Other) = delete;
	FireRed(FireRed&& _Other) noexcept = delete;
	FireRed& operator=(const FireRed& _Other) = delete;
	FireRed& operator=(FireRed&& _Other) noexcept = delete;

protected:

private:

};

