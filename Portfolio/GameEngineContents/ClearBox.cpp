#include "ClearBox.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include <GameEngine/GameEngine.h>

ClearBox::ClearBox() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, AnimTimer_(0.0f)
{
}

ClearBox::~ClearBox() 
{
}

void ClearBox::Start()
{
	Renderer_ = CreateRenderer("pickup_005_Clearchests.bmp", static_cast<int>(ORDER::PLAYER));
}

void ClearBox::Update()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ <= 0.2f)
	{
		Renderer_->SetIndex(3);
	}
	else if (AnimTimer_ <= 0.4f)
	{
		Renderer_->SetIndex(2);
	}
	else if (AnimTimer_ <= 0.6f)
	{
		Renderer_->SetIndex(1);
	}
	else if (AnimTimer_ <= 0.8f)
	{
		Renderer_->SetIndex(0);
		Collision_ = CreateCollision("ClearBox", { 160, 160 });
	}

	if (nullptr != Collision_)
	{
		if (true == Collision_->CollisionCheckRect("Player"))
		{
			GameEngine::GetInst().ChangeLevel("Ending");
		}
	}
}
