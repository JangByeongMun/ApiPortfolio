#include "Stone.h"
#include <GameEngineBase/GameEngineRandom.h>

Stone::Stone() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, StoneType_(0)
{
}

Stone::~Stone() 
{
}

void Stone::BombStone()
{
	switch (StoneType_)
	{
	case 0:
		Renderer_->SetIndex(3);
		break;
	case 1:
		Renderer_->SetIndex(7);
		break;
	case 2:
		Renderer_->SetIndex(7);
		break;
	default:
		break;
	}

	Collision_->Off();
}

void Stone::Create(int _StonType)
{
	StoneType_ = _StonType;
	Renderer_ = CreateRenderer("rocks_basement.bmp");

	switch (StoneType_)
	{
	case 0:
		Renderer_->SetIndex(GameEngineRandom::MainRandom->RandomInt(0, 2));
		break;
	case 1:
		Renderer_->SetIndex(5);
		break;
	case 2:
	{
		int RandomInt = (GameEngineRandom::MainRandom->RandomInt(0, 2));
		Renderer_->SetIndex(6 + (4 * RandomInt));
		break;
	}
	default:
		break;
	}
	Collision_ = CreateCollision("Stone", { 70, 75 });
}

void Stone::Update()
{
	if (true == Collision_->IsUpdate() && Collision_->CollisionCheckRect("Player"))
	{

	}
}
