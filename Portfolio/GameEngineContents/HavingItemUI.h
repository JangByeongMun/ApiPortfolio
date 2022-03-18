#pragma once

// Ό³Έν :
class HavingItemUI
{
public:
	// constrcuter destructer
	HavingItemUI();
	~HavingItemUI();

	// delete Function
	HavingItemUI(const HavingItemUI& _Other) = delete;
	HavingItemUI(HavingItemUI&& _Other) noexcept = delete;
	HavingItemUI& operator=(const HavingItemUI& _Other) = delete;
	HavingItemUI& operator=(HavingItemUI&& _Other) noexcept = delete;

protected:

private:

};

