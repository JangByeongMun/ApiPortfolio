#pragma once
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "MapPos.h"

using namespace std;

// Ό³Έν :
class RoomData;
	class RandomRoomManager
{
private:
	static RandomRoomManager* Inst_;
public:
	inline static RandomRoomManager* GetInst()
	{
		return Inst_;
	}
	inline static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}

		delete Inst_;
		Inst_ = nullptr;
	}

	bool ChangeFloor(const int& _floor);

protected:

private:
	map<int, vector<RoomData*>> AllMaps_;
	map<MapPos, RoomData*> CurrentMaps_;
	int currentFloor_;
	int currentMapCount_;

	// constrcuter destructer
	RandomRoomManager();
	~RandomRoomManager();

	// delete Function
	RandomRoomManager(const RandomRoomManager& _Other) = delete;
	RandomRoomManager(RandomRoomManager&& _Other) noexcept = delete;
	RandomRoomManager& operator=(const RandomRoomManager& _Other) = delete;
	RandomRoomManager& operator=(RandomRoomManager&& _Other) noexcept = delete;
};