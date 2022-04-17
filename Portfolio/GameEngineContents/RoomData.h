#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

// 설명 : 각 방의 정보를 저장하는 데이터
union MapPos;
class RoomData
{
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
		Tile(int _X, int _Y, TileType _Type)
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
		TileType Type_;
	};

public:
	RoomData();
	~RoomData();

	// delete Function
	RoomData(const RoomData& _Other) = delete;
	RoomData(RoomData&& _Other) noexcept = delete;
	RoomData& operator=(const RoomData& _Other) = delete;
	RoomData& operator=(RoomData&& _Other) noexcept = delete;

	bool operator()(const MapPos& _Left, const MapPos& _Right);
	void AddBlock(int _X, int _Y, TileType _Type);
	
	std::vector<Tile> AllBlock_; // {13, 7}
protected:

private:
};