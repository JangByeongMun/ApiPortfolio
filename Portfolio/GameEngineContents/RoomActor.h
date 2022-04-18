#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>

// Ό³Έν :
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

protected:

private:

	void Start() override;
};

