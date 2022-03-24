#pragma once

// 설명 : 각 블럭의 정보
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

// 설명 : 각 방의 정보를 저장하는 데이터
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