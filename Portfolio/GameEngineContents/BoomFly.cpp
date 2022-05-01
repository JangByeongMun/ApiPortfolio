#include "BoomFly.h"
#include <GameEngine/GameEngineImageManager.h>
#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "RoomActor.h"
#include "BoomEffect.h"

BoomFly::BoomFly() 
	: Type_(BoomFlyType::Normal)
	, MoveDir_(1, 1)
{
}

BoomFly::~BoomFly() 
{
}

void BoomFly::Setting(BoomFlyType _Type)
{
	Type_ = _Type;
	Collision_ = CreateCollision("Monster", { 50, 50 });
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	switch (_Type)
	{
	case BoomFlyType::Normal:
		Renderer_->CreateAnimation("monster_096_boomfly.bmp", "Idle", 0, 1, 0.1f, true);
		break;
	case BoomFlyType::Red:
		Renderer_->CreateAnimation("monster_101_redboomfly.bmp", "Idle", 0, 1, 0.1f, true);
		break;
	default:
		break;
	}

	Renderer_->ChangeAnimation("Idle");
	SetHP(20);
	SetMoveSpeed(100.0f);
}

void BoomFly::MonsterUpdate()
{
	MoveZigZag(MoveDir_ * MoveSpeed_ * GameEngineTime::GetDeltaTime());
}

void BoomFly::MonsterDeath()
{
	switch (Type_)
	{
	case BoomFlyType::Normal:
	{
		Collision_->Off();
		GetLevel()->CreateActor<BoomEffect>()->Setting(GetPosition());
		break;
	}
	case BoomFlyType::Red:
	{
		Shoot({ 400, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 300, 300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, 300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -400, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, -300 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 300, -300 }, ProjectileType::ENEMY_BASIC);
		break;
	}
	default:
		break;
	}
}

void BoomFly::MoveZigZag(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");
	float4 AddPivot = Room_->GetPosition() - GameEngineWindow::GetScale().Half();

	// x축이나 y축으로 더이상 갈수없을경우 x나 y중 한군데를 제외하고 이동
	float4 NextPos = GetPosition() + _Value;
	float4 NextPos_x = GetPosition() + float4(_Value.x, _Value.y * -1);
	float4 NextPos_y = GetPosition() + float4(_Value.x * -1, _Value.y);
	int Color = MapColImage_->GetImagePixel(NextPos - AddPivot);
	int Color_x = MapColImage_->GetImagePixel(NextPos_x - AddPivot);
	int Color_y = MapColImage_->GetImagePixel(NextPos_y - AddPivot);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(_Value);
	}
	else if (RGB(0, 0, 0) != Color_x)
	{
		SetMove(float4(_Value.x, 0));
		MoveDir_ = float4(MoveDir_.x, MoveDir_.y * -1);
	}
	else if (RGB(0, 0, 0) != Color_y)
	{
		SetMove(float4(0, _Value.y));
		MoveDir_ = float4(MoveDir_.x * -1, MoveDir_.y);
	}
}
