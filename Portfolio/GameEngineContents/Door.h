#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include "ContentsEnum.h"

// 설명 :
class Door : public GameEngineActor
{
public:
	// constrcuter destructer
	Door();
	~Door();

	// delete Function
	Door(const Door& _Other) = delete;
	Door(Door&& _Other) noexcept = delete;
	Door& operator=(const Door& _Other) = delete;
	Door& operator=(Door&& _Other) noexcept = delete;

	inline DoorType GetType()
	{
		return Type_;
	}
	inline DoorDir GetDir()
	{
		return Dir_;
	}

	void Setting(DoorType _Type, DoorDir _Dir);
	void DoorOpen();
	void DoorClose();

	inline void UnLock()
	{
		IsLock_ = false;
		DoorOpen();
	}
	inline void SetLock(bool _Lock)
	{
		IsLock_ = _Lock;
	}
	inline bool GetLock()
	{
		return IsLock_;
	}

	void SetCloseCollision(GameEngineCollision* _Collision)
	{
		CloseCollision_ = _Collision;
	}

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	GameEngineCollision* Collision_;
	GameEngineCollision* CloseCollision_; // 문 닫혀있을때 벽을 평평하게 할 충돌체
	DoorType Type_;
	DoorDir Dir_;
	bool IsOpen_;
	bool IsLock_;
	float AnimTimer_;

	void Update() override;
	void CloseSetting(DoorType _Type, DoorDir _Dir, std::string _Name);
};

