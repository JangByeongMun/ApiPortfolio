#pragma once

// Ό³Έν :
class SpacebarUI
{
public:
	// constrcuter destructer
	SpacebarUI();
	~SpacebarUI();

	// delete Function
	SpacebarUI(const SpacebarUI& _Other) = delete;
	SpacebarUI(SpacebarUI&& _Other) noexcept = delete;
	SpacebarUI& operator=(const SpacebarUI& _Other) = delete;
	SpacebarUI& operator=(SpacebarUI&& _Other) noexcept = delete;

protected:

private:

};

