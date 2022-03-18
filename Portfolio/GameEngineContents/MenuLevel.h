#pragma once

// Ό³Έν :
class MenuLevel
{
public:
	// constrcuter destructer
	MenuLevel();
	~MenuLevel();

	// delete Function
	MenuLevel(const MenuLevel& _Other) = delete;
	MenuLevel(MenuLevel&& _Other) noexcept = delete;
	MenuLevel& operator=(const MenuLevel& _Other) = delete;
	MenuLevel& operator=(MenuLevel&& _Other) noexcept = delete;

protected:

private:

};

