#include "Hole.h"
#include "ContentsGlobal.h"
#include <GameEngine/GameEngineRenderer.h>

Hole::Hole() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, HoleIndex_(0)
{
}

Hole::~Hole() 
{
}

void Hole::Setting(int _Index)
{
	HoleIndex_ = _Index;
	Collision_ = CreateCollision("Hole", { 50, 50 });

	std::string TmpName = "";
	switch (CurrentFloor)
	{
	case 1:
	case 2:
		TmpName = "grid_pit.bmp";
		break;
	case 3:
		TmpName = "grid_pit_depths.bmp";
		break;
	default:
		break;
	}
	Renderer_ = CreateRenderer(TmpName);
	Renderer_->SetIndex(HoleIndex_);
}