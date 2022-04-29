#include "Mulligoon.h"

Mulligoon::Mulligoon() 
{
}

Mulligoon::~Mulligoon() 
{
}

void Mulligoon::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	//Renderer_->CreateAnimation("monster_061_muliboom.bmp", "Idle", );
}

