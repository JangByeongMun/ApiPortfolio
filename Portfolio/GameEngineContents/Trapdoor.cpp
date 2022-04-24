#include "Trapdoor.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>

Trapdoor::Trapdoor() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, AnimTimer_(0.0f)
	, IsOpen_(false)
{
}

Trapdoor::~Trapdoor() 
{
}

void Trapdoor::Start()
{
	Renderer_ = CreateRenderer("door_20_secrettrapdoor.bmp");
	Renderer_->SetIndex(3);
}

void Trapdoor::Update()
{
	if (nullptr == Collision_) // �����ؼ� ���� �浹ü�� ����� ���ϰ��
	{
		AnimTimer_ += GameEngineTime::GetDeltaTime();

		if (AnimTimer_ >= 1.0f)
		{
			Renderer_->SetIndex(0);
			Collision_ = CreateCollision("Trapdoor", { 50, 50 });
		}
		else if (AnimTimer_ >= 0.8f)
		{
			Renderer_->SetIndex(2);
		}
		else if (AnimTimer_ >= 0.6f)
		{
			Renderer_->SetIndex(1);
		}
		else if (AnimTimer_ >= 0.4f)
		{
			Renderer_->SetIndex(5);
		}
		else if (AnimTimer_ >= 0.2f)
		{
			Renderer_->SetIndex(4);
		}
	}
	else // �浹ü�� �ִ°��
	{
		if (true == IsOpen_)
		{
			if (true == Collision_->CollisionCheckRect("Player"))
			{
				GameEngine::GetInst().ChangeLevel("Loading");
			}
		}
		else
		{
			if (false == Collision_->CollisionCheckRect("Player"))
			{
				TurnOn(true);
			}
		}
	}
}

void Trapdoor::TurnOn(bool _On)
{
	IsOpen_ = _On;
	if (_On)
	{
		Renderer_->SetIndex(0);
	}
	else
	{
		Renderer_->SetIndex(3);
	}
}
