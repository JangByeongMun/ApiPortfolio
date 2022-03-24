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
union MapPos;
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

	bool operator()(const MapPos& _left, const MapPos& _right);

protected:

private:
	char allBlock_[7][13];
	int startX = 200;
	int startY = 100;
	int scaleX = 50;
	int scaleY = 50;
};