#include "Door.h"
#include <string>
#include <GameEngine/GameEngineRenderer.h>
#include "Player.h"

Door::Door() 
	: Collision_(nullptr)
	, Type_()
	, Dir_()
	, IsOpen_(false)
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
		//Name += "02_treasureroomdoor";
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


	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(Name);
		TmpRenderer->SetIndex(1);
		RendererVector_.push_back(TmpRenderer);
	}

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(Name);
		TmpRenderer->SetIndex(2);
		RendererVector_.push_back(TmpRenderer);
	}

	{
		GameEngineRenderer* TmpRenderer = CreateRenderer(Name);
		TmpRenderer->SetIndex(3);
		RendererVector_.push_back(TmpRenderer);
	}

	switch (Dir_)
	{
	case DoorDir::Up:
		RendererVector_[0]->SetPivot({0, 10});
		RendererVector_[1]->SetPivot({-18, 0});
		RendererVector_[2]->SetPivot({18, 0});
		break;
	case DoorDir::Down:
		RendererVector_[0]->SetPivot({ 0, -10 });
		RendererVector_[1]->SetPivot({ 18, 0 });
		RendererVector_[2]->SetPivot({ -18, 0 });
		break;
	case DoorDir::Left:
		RendererVector_[0]->SetPivot({ 10, 0 });
		RendererVector_[1]->SetPivot({ 0, 18 });
		RendererVector_[2]->SetPivot({ 0, -18 });
		break;
	case DoorDir::Right:
		RendererVector_[0]->SetPivot({ -10, 0 });
		RendererVector_[1]->SetPivot({ 0, -18 });
		RendererVector_[2]->SetPivot({ 0, 18 });
		break;
	default:
		break;
	}

	CreateRenderer(Name)->SetIndex(0);
}

void Door::DoorOpen()
{
	IsOpen_ = true;
	RendererVector_[1]->Off();
	RendererVector_[2]->Off();
	Collision_->On();
}

void Door::DoorClose()
{
	IsOpen_ = false;
	RendererVector_[1]->On();
	RendererVector_[2]->On();
	Collision_->Off();
}

void Door::Update()
{
	if (true == Collision_->CollisionCheckRect("Player"))
	{
		Player::MainPlayer->ChangeRoom(Dir_);
	}
}

