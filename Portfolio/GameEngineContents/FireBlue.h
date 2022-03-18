#pragma once

// Ό³Έν :
class FireBlue
{
public:
	// constrcuter destructer
	FireBlue();
	~FireBlue();

	// delete Function
	FireBlue(const FireBlue& _Other) = delete;
	FireBlue(FireBlue&& _Other) noexcept = delete;
	FireBlue& operator=(const FireBlue& _Other) = delete;
	FireBlue& operator=(FireBlue&& _Other) noexcept = delete;

protected:

private:

};

