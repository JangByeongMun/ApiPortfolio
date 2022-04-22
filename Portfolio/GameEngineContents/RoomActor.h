#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <vector>
#include "RoomData.h"

class Door;
class Monster;
class RoomActor : public GameEngineActor
{
public:
	// constrcuter destructer
	RoomActor();
	~RoomActor();

	// delete Function
	RoomActor(const RoomActor& _Other) = delete;
	RoomActor(RoomActor&& _Other) noexcept = delete;
	RoomActor& operator=(const RoomActor& _Other) = delete;
	RoomActor& operator=(RoomActor&& _Other) noexcept = delete;

	inline void SetData(RoomData _Data)
	{
		Data_ = _Data;
	}
	inline void SetPos(float4 _Pos)
	{
		Pos_ = _Pos;
	}

	inline RoomData& GetData()
	{
		return Data_;
	}
	inline float4& GetPos()
	{
		return Pos_;
	}

	void MinusMonsterCount();
	inline int GetMonsterCount()
	{
		return MonsterCount_;
	}

	void Setting();
	Door* FindDoor(DoorDir _Dir);
	bool IsCurrentRoom();

	void OpenAllDoor();
	void CloseAllDoor();

protected:

private:
	std::vector<Door*> DoorVector_;
	std::vector<Monster*> MonsterVector_;
	RoomData Data_;
	float4 Pos_;
	int MonsterCount_;

	void Start() override;
	void DoorSetting();
};