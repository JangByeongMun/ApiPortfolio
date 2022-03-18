#pragma once

// Ό³Έν :
class OptionUI
{
public:
	// constrcuter destructer
	OptionUI();
	~OptionUI();

	// delete Function
	OptionUI(const OptionUI& _Other) = delete;
	OptionUI(OptionUI&& _Other) noexcept = delete;
	OptionUI& operator=(const OptionUI& _Other) = delete;
	OptionUI& operator=(OptionUI&& _Other) noexcept = delete;

protected:

private:

};

