#pragma once

// Ό³Έν :
class MoneyItem
{
public:
	// constrcuter destructer
	MoneyItem();
	~MoneyItem();

	// delete Function
	MoneyItem(const MoneyItem& _Other) = delete;
	MoneyItem(MoneyItem&& _Other) noexcept = delete;
	MoneyItem& operator=(const MoneyItem& _Other) = delete;
	MoneyItem& operator=(MoneyItem&& _Other) noexcept = delete;

protected:

private:

};

