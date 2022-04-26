#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>

class RoomActor;
class ItemBase : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemBase();
	~ItemBase();

	// delete Function
	ItemBase(const ItemBase& _Other) = delete;
	ItemBase(ItemBase&& _Other) noexcept = delete;
	ItemBase& operator=(const ItemBase& _Other) = delete;
	ItemBase& operator=(ItemBase&& _Other) noexcept = delete;

	inline void AddDir(float4 _Dir)
	{
		Dir_ += _Dir;
	}
	void SetRoom(float4 _Pos);
	bool CanMove(float4 _Value);
	void SetObjectMove();

protected:
	RoomActor* Room_;
	GameEngineImage* MapColImage_;
	float4 Dir_;
	GameEngineCollision* Collision_;

};

