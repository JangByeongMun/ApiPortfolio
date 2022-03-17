#pragma once

// Ό³Έν :
class Credit
{
public:
	// constrcuter destructer
	Credit();
	~Credit();

	// delete Function
	Credit(const Credit& _Other) = delete;
	Credit(Credit&& _Other) noexcept = delete;
	Credit& operator=(const Credit& _Other) = delete;
	Credit& operator=(Credit&& _Other) noexcept = delete;

protected:

private:

};

