#include "FloatingKnight.h"

FloatingKnight::FloatingKnight() 
	: IsAttack_(false)
{
}

FloatingKnight::~FloatingKnight() 
{
}

void FloatingKnight::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	Renderer_->CreateAnimation("monster_254_floating knight.bmp", "Up", 2, 2, 0.1f, false);
	Renderer_->CreateAnimation("monster_254_floating knight.bmp", "Down", 0, 0, 0.1f, false);
	Renderer_->CreateAnimation("monster_254_floating knight.bmp", "Left", 3, 3, 0.1f, false);
	Renderer_->CreateAnimation("monster_254_floating knight.bmp", "Right", 1, 1, 0.1f, false);
	Renderer_->ChangeAnimation("Down");

	Collision_ = CreateCollision("NoDamageMonster", { 70, 70 });

	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 10, 75 }, {-37.5f, 0});
		TmpCollision_->Off();
		CollisionVector_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 10, 75 }, { 37.5f, 0 });
		TmpCollision_->Off();
		CollisionVector_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 75, 10 }, { 0, -37.5f });
		TmpCollision_->Off();
		CollisionVector_.push_back(TmpCollision_);
	}
	{
		GameEngineCollision* TmpCollision_ = CreateCollision("Monster", { 75, 10 }, { 0, 37.5f });
		TmpCollision_->Off();
		CollisionVector_.push_back(TmpCollision_);
	}

	SetHP(20.0f);
	SetMoveSpeed(150.0f);
	SetAttackDelay(3.0f);

	MoveDir_ = float4(GameEngineRandom::MainRandom->RandomFloat(-2, 2), GameEngineRandom::MainRandom->RandomFloat(-2, 2));
	int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 1);
	if (0 == RandomInt)
	{
		MoveDir_.x = 0;
		if (MoveDir_.y >= 0)
		{
			Renderer_->ChangeAnimation("Down");
			ChangeCollision(2);
		}
		else
		{
			Renderer_->ChangeAnimation("Up");
			ChangeCollision(3);
		}
	}
	else
	{
		MoveDir_.y = 0;
		if (MoveDir_.x >= 0)
		{
			Renderer_->ChangeAnimation("Right");
			ChangeCollision(0);
		}
		else
		{
			Renderer_->ChangeAnimation("Left");
			ChangeCollision(1);
		}
	}
	MoveDir_.Normal2D();
}

void FloatingKnight::MonsterUpdate()
{
	AttackTimer_ += GameEngineTime::GetDeltaTime();
	if (AttackTimer_ >= AttackDelay_)
	{
		AttackTimer_ = 0.0f;
		MoveDir_ = float4(GameEngineRandom::MainRandom->RandomFloat(-2, 2), GameEngineRandom::MainRandom->RandomFloat(-2, 2));
		int RandomInt = GameEngineRandom::MainRandom->RandomInt(0, 1);
		if (0 == RandomInt)
		{
			MoveDir_.x = 0;
			if (MoveDir_.y >= 0)
			{
				Renderer_->ChangeAnimation("Down");
				ChangeCollision(2);
			}
			else
			{
				Renderer_->ChangeAnimation("Up");
				ChangeCollision(3);
			}
		}
		else
		{
			MoveDir_.y = 0;
			if (MoveDir_.x >= 0)
			{
				Renderer_->ChangeAnimation("Right");
				ChangeCollision(0);
			}
			else
			{
				Renderer_->ChangeAnimation("Left");
				ChangeCollision(1);
			}
		}
		MoveDir_.Normal2D();
	}

	if (false == MonsterSetMoveToFlyReturn(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_))
	{
		AttackTimer_ += AttackDelay_;
	}
}

void FloatingKnight::ChangeCollision(int _Index)
{
	for (int i = 0; i < CollisionVector_.size(); i++)
	{
		if (i == _Index)
		{
			CollisionVector_[i]->On();
		}
		else
		{
			CollisionVector_[i]->Off();
		}
	}
}

