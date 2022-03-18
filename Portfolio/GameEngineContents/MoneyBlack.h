#pragma once

// Ό³Έν :
class MoneyBlack
{
public:
	// constrcuter destructer
	MoneyBlack();
	~MoneyBlack();

	// delete Function
	MoneyBlack(const MoneyBlack& _Other) = delete;
	MoneyBlack(MoneyBlack&& _Other) noexcept = delete;
	MoneyBlack& operator=(const MoneyBlack& _Other) = delete;
	MoneyBlack& operator=(MoneyBlack&& _Other) noexcept = delete;

protected:

private:

};

