#include "Stone.h"
#include <GameEngineBase/GameEngineRandom.h>

Stone::Stone() 
{
}

Stone::~Stone() 
{
}

void Stone::BombStone()
{
	Renderer_->SetIndex(3);
	Collision_->Death();
}

void Stone::Start()
{
	Renderer_ = CreateRenderer("rocks_basement.bmp");
	Renderer_->SetIndex(GameEngineRandom::MainRandom->RandomInt(0, 2));
	Collision_ = CreateCollision("Stone", {70, 75});
}