#include "NewBoxItem.h"
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsEnum.h"

NewBoxItem::NewBoxItem() 
{
}

NewBoxItem::~NewBoxItem() 
{
}

void NewBoxItem::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	std::string TmpName = "pickup_005_chests_Gold.bmp";

	Renderer_->CreateAnimation(TmpName, "Idle", 0, 0, 0.1f, true);
	Renderer_->CreateAnimation(TmpName, "Appear", 6, 8, 0.1f, true);
	Renderer_->ChangeAnimation("Idle");

	ChangeState(NewBoxState::Appear);
}

void NewBoxItem::Update()
{
	switch (State_)
	{
	case NewBoxState::Appear:
		AppearUpdate();
		break;
	}
}

void NewBoxItem::ChangeState(NewBoxState _State)
{
	if (State_ == _State)
	{
		return;
	}

	switch (_State)
	{
	case NewBoxState::Appear:
		AppearStart();
		break;
	case NewBoxState::Idle:
		IdleStart();
		break;
	}
	State_ = _State;
}

void NewBoxItem::AppearStart()
{
	AnimTimer_ = 0.0f;
	Renderer_->ChangeAnimation("Appear");
}

void NewBoxItem::IdleStart()
{
	Renderer_->ChangeAnimation("Idle");
}

void NewBoxItem::AppearUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	if (AnimTimer_ >= 0.5f)
	{
		ChangeState(NewBoxState::Idle);
	}
}
