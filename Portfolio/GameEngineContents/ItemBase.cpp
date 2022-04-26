#include "ItemBase.h"
#include "RandomRoomManager.h"
#include "RoomActor.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "RandomRoomManager.h"

ItemBase::ItemBase() 
	: Room_(nullptr)
	, MapColImage_(nullptr)
	, Dir_({0, 0})
	, Collision_(nullptr)
{
}

ItemBase::~ItemBase() 
{
}

void ItemBase::SetRoom(float4 _Pos)
{
	Room_ = RandomRoomManager::GetInst()->FindRoom(_Pos);
	MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");
}

bool ItemBase::CanMove(float4 _Value)
{
	if (nullptr == Room_)
	{
		SetRoom(Player::MainPlayer->GetCurrentRoomPos());
	}
	// 룸마다 크기는 같으므로 보정치를 줘서 어떤룸에서도 똑같은 위치만큼만 이동할수있도록
	float4 AddPivot = Room_->GetPosition() - GameEngineWindow::GetScale().Half();
	int Color = MapColImage_->GetImagePixel(GetPosition() + _Value - AddPivot);

	if (nullptr == Collision_)
	{
		return false;
	}

	if (
		RGB(0, 0, 0) != Color &&
		false == Collision_->NextPosCollisionCheckRect("Stone", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Wall", _Value) &&
		false == Collision_->NextPosCollisionCheckRect("Poop", _Value)
		)
	{
		return true;
	}

	return false;
}
void ItemBase::SetObjectMove()
{
	Dir_.Limit2D(4.0f);
	if (true == CanMove(Dir_))
	{
		SetMove(Dir_);
	}
	else if (true == CanMove(float4(Dir_.x, 0)))
	{
		SetMove(float4(Dir_.x, 0));
	}
	else if (true == CanMove(float4(0, Dir_.y)))
	{
		SetMove(float4(0, Dir_.y));
	}

	if (Dir_.Len2D() >= 1.0f)
	{
		Dir_ += -Dir_ * GameEngineTime::GetDeltaTime() * 3.0f;
	}
	else
	{
		Dir_ = float4::ZERO;
	}
}