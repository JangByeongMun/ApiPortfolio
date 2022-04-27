#pragma once
#include <map>
#include <vector>
#include "MapPos.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include "ContentsGlobal.h"	

// Ό³Έν :
class RoomData;
class RoomActor;
class RandomRoomManager : public GameEngineActor
{
private:
	static RandomRoomManager* Inst_;
public:
	inline static RandomRoomManager* GetInst()
	{
		return Inst_;
	}
	inline static void SetInst(RandomRoomManager* _Value)
	{
		Inst_ = _Value;
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

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	inline int GetCurrentFloor()
	{
		return CurrentFloor;
	}

	bool ChangeFloor(const int& _floor);
	
	float4 RandomPos();
	float4 RandomCornerPos();

	RoomData RandomData();
	RoomData RandomTreasureRoomData();
	RoomData RandomBossRoomData();
	RoomData RandomShopRoomData();

	bool ExistPos(float4 _Pos);
	bool CornerPos(float4 _Pos);
	int ConnectedRoomCount(float4 _Pos);
	RoomActor* FindRoom(float4 _Pos);
	RoomActor* GetCurrentRoom();

	inline std::vector<RoomActor*> GetCurrentRooms()
	{
		return CurrentRooms_;
	}

protected:

private:
	friend GameEngineLevel;

	std::map<int, std::vector<RoomData>> AllRooms_;
	std::map<int, std::vector<RoomData>> AllTreasureRooms_;
	std::map<int, std::vector<RoomData>> AllBossRooms_;
	std::map<int, std::vector<RoomData>> AllShopRooms_;

	std::vector<RoomActor*> CurrentRooms_;
	int CurrentMapCount_;

	std::string FloorName_;
	GameEngineRenderer* FloorRenderer_;
	float AnimTimer_;

	// constrcuter destructer
	RandomRoomManager();
	~RandomRoomManager();

	// delete Function
	RandomRoomManager(const RandomRoomManager& _Other) = delete;
	RandomRoomManager(RandomRoomManager&& _Other) noexcept = delete;
	RandomRoomManager& operator=(const RandomRoomManager& _Other) = delete;
	RandomRoomManager& operator=(RandomRoomManager&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
};