#pragma once
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

using namespace std;

// Ό³Έν :
class RoomData;
class RandomRoomManager
{
private:
	static RandomRoomManager* inst_;
public:
	inline static RandomRoomManager* GetInst()
	{
		return inst_;
	}
	inline static void Destroy()
	{
		if (nullptr == inst_)
		{
			return;
		}

		delete inst_;
		inst_ = nullptr;
	}

	bool ChangeFloor(const int& _floor);

protected:

private:
	//map<int, vector<RoomData*>> allMaps_;
	//map<float4, RoomData*> currentMaps_;
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

