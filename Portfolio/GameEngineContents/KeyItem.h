#pragma once

// Ό³Έν :
class KeyItem
{
public:
	// constrcuter destructer
	KeyItem();
	~KeyItem();

	// delete Function
	KeyItem(const KeyItem& _Other) = delete;
	KeyItem(KeyItem&& _Other) noexcept = delete;
	KeyItem& operator=(const KeyItem& _Other) = delete;
	KeyItem& operator=(KeyItem&& _Other) noexcept = delete;

protected:

private:

};

