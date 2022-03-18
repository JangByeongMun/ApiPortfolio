#pragma once

// Ό³Έν :
class Fire
{
public:
	// constrcuter destructer
	Fire();
	~Fire();

	// delete Function
	Fire(const Fire& _Other) = delete;
	Fire(Fire&& _Other) noexcept = delete;
	Fire& operator=(const Fire& _Other) = delete;
	Fire& operator=(Fire&& _Other) noexcept = delete;

protected:

private:

};

