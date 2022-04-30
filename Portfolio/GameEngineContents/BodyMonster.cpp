#include "BodyMonster.h"

BodyMonster::BodyMonster()
	: BodyRenderer_(nullptr)
{
}

BodyMonster::~BodyMonster() 
{
}

void BodyMonster::BodySetting()
{
	BodyRenderer_ = CreateRenderer(static_cast<int>(ORDER::BACKPLAYER), RenderPivot::CENTER, { 0, 35 });
	BodyRenderer_->CreateAnimation("monster_000_bodies01_Right.bmp", "Idle", 0, 0, 0.1f, false);
	BodyRenderer_->CreateAnimation("monster_000_bodies01_Right.bmp", "Move_Up", 0, 9, 0.1f, true);
	BodyRenderer_->CreateAnimation("monster_000_bodies01_Right.bmp", "Move_Down", 0, 9, 0.1f, true);
	BodyRenderer_->CreateAnimation("monster_000_bodies01_Right.bmp", "Move_Right", 10, 19, 0.1f, true);
	BodyRenderer_->CreateAnimation("monster_000_bodies01_Left.bmp", "Move_Left", 10, 19, 0.1f, true);
	BodyRenderer_->ChangeAnimation("Idle");
}
void BodyMonster::BodySettingBlood()
{
	BodyRenderer_ = CreateRenderer(static_cast<int>(ORDER::BACKPLAYER), RenderPivot::CENTER, { 0, 35 });
	BodyRenderer_->CreateAnimation("monster_000_bodies02_Right.bmp", "Idle", 0, 0, 0.1f, false);
	BodyRenderer_->CreateAnimation("monster_000_bodies02_Right.bmp", "Move_Up", 0, 9, 0.1f, true);
	BodyRenderer_->CreateAnimation("monster_000_bodies02_Right.bmp", "Move_Down", 0, 9, 0.1f, true);
	BodyRenderer_->CreateAnimation("monster_000_bodies02_Right.bmp", "Move_Right", 10, 19, 0.1f, true);
	BodyRenderer_->CreateAnimation("monster_000_bodies02_Left.bmp", "Move_Left", 10, 19, 0.1f, true);
	BodyRenderer_->ChangeAnimation("Idle");
}

void BodyMonster::BodyUpdate(float4 _Pos)
{
	MoveDir TmpDir = GetDir(_Pos);
	switch (TmpDir)
	{
	case MoveDir::UP:
		BodyRenderer_->ChangeAnimation("Move_Up");
		break;
	case MoveDir::DOWN:
		BodyRenderer_->ChangeAnimation("Move_Down");
		break;
	case MoveDir::LEFT:
		BodyRenderer_->ChangeAnimation("Move_Left");
		break;
	case MoveDir::RIGHT:
		BodyRenderer_->ChangeAnimation("Move_Right");
		break;
	default:
		break;
	}
}
MoveDir BodyMonster::GetDir(float4 _Dir)
{
	MoveDir ReturnDir = MoveDir::UP;
	float absX = _Dir.x;
	float absY = _Dir.y;
	if (absX < 0)
	{
		absX *= -1;
	}
	if (absY < 0)
	{
		absY *= -1;
	}

	if (absY >= absX)
	{
		if (_Dir.y > 0)
		{
			ReturnDir = MoveDir::DOWN;
		}
		else
		{
			ReturnDir = MoveDir::UP;
		}
	}
	else
	{
		if (_Dir.x > 0)
		{
			ReturnDir = MoveDir::RIGHT;
		}
		else
		{
			ReturnDir = MoveDir::LEFT;
		}
	}

	return ReturnDir;
}