#pragma once

// Ό³Έν :
class BombItem
{
public:
	// constrcuter destructer
	BombItem();
	~BombItem();

	// delete Function
	BombItem(const BombItem& _Other) = delete;
	BombItem(BombItem&& _Other) noexcept = delete;
	BombItem& operator=(const BombItem& _Other) = delete;
	BombItem& operator=(BombItem&& _Other) noexcept = delete;

protected:

private:

};

