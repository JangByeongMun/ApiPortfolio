#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

// 설명 : 각 방의 정보를 저장하는 데이터
union MapPos;
class RandomRoomManager;
class RoomActor;
class Monster;
class RoomData
{
	friend RandomRoomManager;
	friend RoomActor;
public:
	class BlockData
	{
	public:
		BlockData(int _X, int _Y, BlockType _Type)
			: X_(_X)
			, Y_(_Y)
			, Type_(_Type)
		{
		}
		~BlockData()
		{

		}

		int X_;
		int Y_;
		BlockType Type_;
	};
	class MonsterData
	{
	public:
		MonsterData(int _X, int _Y, MonsterType _Type)
			: X_(_X)
			, Y_(_Y)
			, Type_(_Type)
		{
		}
		~MonsterData()
		{
		}

		int X_;
		int Y_;
		MonsterType Type_;
	};

public:
	RoomData();
	RoomData(const RoomData& _Other);
	~RoomData();

	RoomData& operator=(RoomData& _Other);

	void AddBlock(int _X, int _Y, BlockType _Type);
	void AddMonster(int _X, int _Y, MonsterType _Type);
	
	inline void SetRoomType(RoomType _Type)
	{
		RoomType_ = _Type;
	}
	inline RoomType GetRoomType()
	{
		return RoomType_;
	}
	inline bool IsDefaultType()
	{
		return RoomType_ == RoomType::Default;
	}

protected:

private:
	RoomType RoomType_;
	std::vector<BlockData> AllBlock_; // {13, 7}
	std::vector<MonsterData> AllMonster_;
};