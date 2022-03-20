#pragma once

// ���� : �� ���� ����
enum class BlockData
{
	NORMAL = 0,
	FIRE,
	FIREBLUE,
	FIRERED,
	HOLE,
	POOP,
	POOPRED,
	STONE,
	STONEBLACK,
	THORN,

	END,
};

// ���� : �� ���� ������ �����ϴ� ������
class RoomData
{
public:
	RoomData();
	~RoomData();

	// delete Function
	RoomData(const RoomData& _Other) = delete;
	RoomData(RoomData&& _Other) noexcept = delete;
	RoomData& operator=(const RoomData& _Other) = delete;
	RoomData& operator=(RoomData&& _Other) noexcept = delete;

	void Render();

protected:

private:
	int allBlock_[7][13];
	int startX = 200;
	int startY = 100;
	int scaleX = 50;
	int scaleY = 50;
};