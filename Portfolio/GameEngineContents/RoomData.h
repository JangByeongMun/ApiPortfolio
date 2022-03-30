#pragma once

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

	bool operator()(const MapPos& _Left, const MapPos& _Right);

protected:

private:
	char AllBlock_[7][13];
	int StartX = 200;
	int StartY = 100;
	int ScaleX = 50;
	int ScaleY = 50;
};