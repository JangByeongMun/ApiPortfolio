#include "Door.h"
#include <string>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"

Door::Door() 
	: Collision_(nullptr)
	, Type_()
	, Dir_()
	, IsOpen_(false)
	, IsLock_(false)
	, AnimTimer_(0.0f)
{
}

Door::~Door() 
{
}

void Door::Setting(DoorType _Type, DoorDir _Dir)
{
	Collision_ = CreateCollision("Door", { 30, 30 });

	std::string Name = "door_";
	Type_ = _Type;
	Dir_ = _Dir;

	switch (Type_)
	{
	case DoorType::Default:
		Name += "01_normaldoor";
		break;
	case DoorType::Treasure:
		Name += "02_treasureroomdoor";
		break;
	case DoorType::Boss:
		Name += "10_bossroomdoor";
		break;
	case DoorType::Max:
		break;
	default:
		break;
	}

	switch (Dir_)
	{
	case DoorDir::Up:
		Collision_->SetPivot({0, -40});
		Name += "_Up.bmp";
		break;
	case DoorDir::Down:
		Collision_->SetPivot({ 0, 5 });
		Name += "_Down.bmp";
		break;
	case DoorDir::Left:
		Collision_->SetPivot({ -20, 0 });
		Name += "_Left.bmp";
		break;
	case DoorDir::Right:
		Collision_->SetPivot({ 20, 0 });
		Name += "_Right.bmp";
		break;
	default:
		break;
	}

	CloseSetting(_Type, _Dir, Name);
	CreateRenderer(Name)->SetIndex(0);
}

void Door::DoorOpen()
{
	CloseCollision_->Off();

	if (true == IsLock_)
	{
		return;
	}

	IsOpen_ = true;
	RendererVector_[1]->Off();
	RendererVector_[2]->Off();
}

void Door::DoorClose()
{
	CloseCollision_->On();

	IsOpen_ = false;
	RendererVector_[1]->On();
	RendererVector_[2]->On();
}

void Door::Update()
{
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		if (IsOpen_)
		{
			Player::MainPlayer->ChangeRoom(Dir_);
		}
		else if (IsLock_)
		{
			if (true == Player::MainPlayer->HaveKey())
			{
				Player::MainPlayer->MinusItem(ItemType::Key, 1);
				UnLock();
			}
		}
	}
}

void Door::CloseSetting(DoorType _Type, DoorDir _Dir, std::string _Name)
{
	switch (_Type)
	{
	case DoorType::Default:
	{
		for (int i = 1; i <= 3; i++)
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer(_Name);
			TmpRenderer->SetIndex(i);
			RendererVector_.push_back(TmpRenderer);
		}
		switch (Dir_)
		{
		case DoorDir::Up:
			RendererVector_[0]->SetPivot({ 0, 10 });
			RendererVector_[1]->SetPivot({ -18, 7 });
			RendererVector_[2]->SetPivot({ 18, 7 });
			break;
		case DoorDir::Down:
			RendererVector_[0]->SetPivot({ 0, -10 });
			RendererVector_[1]->SetPivot({ 18, -7 });
			RendererVector_[2]->SetPivot({ -18, -7 });
			break;
		case DoorDir::Left:
			RendererVector_[0]->SetPivot({ 10, 0 });
			RendererVector_[1]->SetPivot({ 7, 18 });
			RendererVector_[2]->SetPivot({ 7, -18 });
			break;
		case DoorDir::Right:
			RendererVector_[0]->SetPivot({ -10, 0 });
			RendererVector_[1]->SetPivot({ -7, -18 });
			RendererVector_[2]->SetPivot({ -7, 18 });
			break;
		default:
			break;
		}
		break;
	}
	case DoorType::Treasure:
	{
		for (int i = 1; i <= 2; i++)
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer(_Name);
			TmpRenderer->SetIndex(i);
			RendererVector_.push_back(TmpRenderer);
		}
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer(_Name);
			TmpRenderer->SetIndex(5);
			RendererVector_.push_back(TmpRenderer);
		}
		switch (Dir_)
		{
		case DoorDir::Up:
			RendererVector_[0]->SetPivot({ 0, 10 });
			RendererVector_[1]->SetPivot({ -18, 10 });
			RendererVector_[2]->SetPivot({ 10, 10 });
			break;
		case DoorDir::Down:
			RendererVector_[0]->SetPivot({ 0, -10 });
			RendererVector_[1]->SetPivot({ 18, -10 });
			RendererVector_[2]->SetPivot({ -10, -10 });
			break;
		case DoorDir::Left:
			RendererVector_[0]->SetPivot({ 10, 0 });
			RendererVector_[1]->SetPivot({ 10, 18 });
			RendererVector_[2]->SetPivot({ 10, -10 });
			break;
		case DoorDir::Right:
			RendererVector_[0]->SetPivot({ -10, 0 });
			RendererVector_[1]->SetPivot({ -10, -18 });
			RendererVector_[2]->SetPivot({ -10, 10 });
			break;
		default:
			break;
		}
		break;
	}
	case DoorType::Boss:
	{
		for (int i = 1; i <= 3; i++)
		{
			GameEngineRenderer* TmpRenderer = CreateRenderer(_Name);
			TmpRenderer->SetIndex(i);
			RendererVector_.push_back(TmpRenderer);
		}
		switch (Dir_)
		{
		case DoorDir::Up:
			RendererVector_[0]->SetScale({190, 160});
			RendererVector_[0]->SetPivot({ 0, 12 });
			RendererVector_[1]->SetPivot({ -18, 12 });
			RendererVector_[2]->SetPivot({ 18, 12 });
			break;
		case DoorDir::Down:
			RendererVector_[0]->SetScale({ 190, 160 });
			RendererVector_[0]->SetPivot({ 0, -12 });
			RendererVector_[1]->SetPivot({ 18, -12 });
			RendererVector_[2]->SetPivot({ -18, -12 });
			break;
		case DoorDir::Left:
			RendererVector_[0]->SetScale({ 160, 190 });
			RendererVector_[0]->SetPivot({ 12, 0 });
			RendererVector_[1]->SetPivot({ 12, 18 });
			RendererVector_[2]->SetPivot({ 12, -18 });
			break;
		case DoorDir::Right:
			RendererVector_[0]->SetScale({ 160, 190 });
			RendererVector_[0]->SetPivot({ -12, 0 });
			RendererVector_[1]->SetPivot({ -12, -18 });
			RendererVector_[2]->SetPivot({ -12, 18 });
			break;
		default:
			break;
		}
		break;
	}
	case DoorType::Max:
		break;
	default:
		break;
	}
}

