#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <vector>
#include "RoomData.h"

class Door;
class Monster;
class Trapdoor;
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
	void MinusBossCount();
	void OpenNextStage();

	inline int GetMonsterCount()
	{
		return MonsterCount_;
	}
	inline int GetBossCount()
	{
		return BossCount_;
	}

	void Setting();
	Door* FindDoor(DoorDir _Dir);
	bool IsCurrentRoom();

	void OpenAllDoor();
	void CloseAllDoor();

	void SetBossHPUI(float _Value);

	inline Trapdoor* GetTrapdoor()
	{
		return Trapdoor_;
	}

protected:

private:
	std::vector<Door*> DoorVector_;
	std::vector<Monster*> MonsterVector_;
	std::vector<GameEngineCollision*> CloseCollisionVector_; // 문닫혔을때 벽 평평하게 만들기용
	std::vector <GameEngineRenderer*> BossHpRendererVector_;
	RoomData Data_;
	float4 Pos_;
	int MonsterCount_;
	int BossCount_;

	Trapdoor* Trapdoor_;

	void Start() override;
	void DoorSetting();
};