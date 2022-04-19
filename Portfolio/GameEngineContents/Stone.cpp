#include "Stone.h"
#include <GameEngineBase/GameEngineRandom.h>

Stone::Stone() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, IsBlack_(false)
{
}

Stone::~Stone() 
{
}

void Stone::BombStone()
{
	if (IsBlack_)
	{
		Renderer_->SetIndex(7);
	}
	else
	{
		Renderer_->SetIndex(3);
	}
	Renderer_->SetIndex(3);
	Collision_->Death();
}

void Stone::Create(bool _IsBlack)
{
	IsBlack_ = _IsBlack;
	Renderer_ = CreateRenderer("rocks_basement.bmp");

	if (IsBlack_)
	{
		Renderer_->SetIndex(5);
	}
	else
	{
		Renderer_->SetIndex(GameEngineRandom::MainRandom->RandomInt(0, 2));
	}
	Collision_ = CreateCollision("Stone", { 70, 75 });
}

void Stone::Update()
{
	if (Collision_->CollisionCheckRect("Player"))
	{

	}
}
