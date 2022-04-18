#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

// 설명 : 각 방의 정보를 저장하는 데이터
union MapPos;
class RandomRoomManager;
class RoomData
{
	friend RandomRoomManager;
public:
	class Tile
	{
	public:
		Tile()
			: X_()
			, Y_()
			, Type_()
		{
		}
		Tile(int _X, int _Y, BlockData _Type)
			: X_(_X)
			, Y_(_Y)
			, Type_(_Type)
		{
		}
		~Tile()
		{

		}

		int X_;
		int Y_;
		BlockData Type_;
	};

public:
	RoomData();
	RoomData(const RoomData& _other);
	~RoomData();

	// delete Function
	RoomData& operator=(const RoomData& _Other) = delete;
	RoomData& operator=(RoomData&& _Other) noexcept = delete;

	bool operator()(const MapPos& _Left, const MapPos& _Right);
	void AddBlock(int _X, int _Y, BlockData _Type);
	
protected:

private:
	std::vector<Tile> AllBlock_; // {13, 7}
};