#pragma once

// Ό³Έν :
class Stone
{
public:
	// constrcuter destructer
	Stone();
	~Stone();

	// delete Function
	Stone(const Stone& _Other) = delete;
	Stone(Stone&& _Other) noexcept = delete;
	Stone& operator=(const Stone& _Other) = delete;
	Stone& operator=(Stone&& _Other) noexcept = delete;

protected:

private:

};

