#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include "ContentsEnum.h"

// Ό³Έν :
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

protected:

private:
	std::vector<GameEngineRenderer*> RendererVector_;
	GameEngineCollision* Collision_;
	DoorType Type_;
	DoorDir Dir_;
	bool IsOpen_;
	float AnimTimer_;

	void Update() override;
};

