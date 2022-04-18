#pragma once
#include <GameEngine/GameEngineActor.h>
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

	void Setting(DoorType _Type, DoorDir _Dir);

protected:

private:
	DoorType Type_;
	DoorDir Dir_;

};

