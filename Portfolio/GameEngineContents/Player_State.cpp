#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>

// Start
void Player::BodyIdleStart()
{
	BodyRender_->ChangeAnimation(GetBodyAnimationName() + "Idle");
}
void Player::BodyMoveStart()
{

}

void Player::HeadIdleStart()
{
	HeadRender_->ChangeAnimation(GetHeadAnimationName() + "Idle");
	for (int i = 0; i < HeadAddRender_.size(); i++)
	{
		HeadAddRender_[i]->ChangeAnimation("Idle");
	}
}
void Player::HeadAttackStart()
{

}
void Player::HeadMoveStart()
{

}


// Update
void Player::BodyIdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeBodyState(PlayerBodyState::Move);
		return;
	}

	if (false == MoveDir_.IsZero2D())
	{
		MoveDir_ += -MoveDir_ * GameEngineTime::GetDeltaTime() * 10;

		if (0.05f >= MoveDir_.Len2D())
		{
			MoveDir_ = float4::ZERO;
		}

		PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_ * 450);
	}
}
void Player::BodyMoveUpdate()
{
	if (false == IsMoveKey())
	{
		ChangeBodyState(PlayerBodyState::Idle);
		return;
	}

	// 동시에 여러 키를 눌렀을때 대각선으로 움직일수있고, 그때 위, 아래 움직이는 애니메이션이므로 else가 아니라 전부 if로 구현
	std::string ChangeDirText = "Idle";
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * 5;
		ChangeDirText = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 5;
		ChangeDirText = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ += float4::UP * GameEngineTime::GetDeltaTime() * 5;
		ChangeDirText = "Up";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 5;
		ChangeDirText = "Down";
	}
	MoveDir_.Limit2D(1.0f);

	BodyRender_->ChangeAnimation(GetBodyAnimationName() + ChangeDirText);

	// Speed는 인게임의 스피드수치, 450은 움직이는걸보고 대충 맞춘 값
	PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_ * 450);
}

void Player::HeadIdleUpdate()
{
	if (true == IsAttackKey())
	{
		ChangeHeadState(PlayerHeadState::Attack);
		return;
	}
	if (true == IsMoveKey())
	{
		ChangeHeadState(PlayerHeadState::Move);
		return;
	}
}
void Player::HeadAttackUpdate()
{
	if (false == IsAttackKey())
	{
		ChangeHeadState(PlayerHeadState::Idle);
		return;
	}

	CurrentAttackTime_ += GameEngineTime::GetDeltaTime();
	std::string ChangeDirText = "Idle";
	float4 AttackDir = float4::ZERO;
	float TearDelay = 1 / AttackSpeed_;

	if (true == GameEngineInput::GetInst()->IsPress("AttackLeft"))
	{
		AttackDir = float4::LEFT;
		ChangeDirText = "Left";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackRight"))
	{
		AttackDir = float4::RIGHT;
		ChangeDirText = "Right";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackUp"))
	{
		AttackDir = float4::UP;
		ChangeDirText = "Up";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackDown"))
	{
		AttackDir = float4::DOWN;
		ChangeDirText = "Down";
	}

	if (NextAttackTime_ <= CurrentAttackTime_ && false == AttackDir.IsZero2D())
	{
		Shoot(AttackDir * ShotSpeed_ * 550, ProjectileType::PLAYER_BASIC, AttackDir * 30);

		HeadRender_->ChangeAnimation(GetHeadAnimationName() + ChangeDirText + "_2");

		NextAttackTime_ = CurrentAttackTime_ + TearDelay;

		// 부가적인 악세사리들 애니메이션도 실행

		for (int i = 0; i < HeadAddRender_.size(); i++)
		{
			HeadAddRender_[i]->ChangeAnimation(ChangeDirText + "_2");
		}
		return;
	}

	if (true == HeadRender_->IsEndAnimation())
	{
		HeadRender_->ChangeAnimation(GetHeadAnimationName() + ChangeDirText + "_1");
		for (int i = 0; i < HeadAddRender_.size(); i++)
		{
			HeadAddRender_[i]->ChangeAnimation(ChangeDirText + "_1");
		}
	}
}
void Player::HeadMoveUpdate()
{
	if (true == IsAttackKey())
	{
		ChangeHeadState(PlayerHeadState::Attack);
		return;
	}

	// 
	std::string ChangeDirText = "Idle";
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		ChangeDirText = "Left_1";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		ChangeDirText = "Right_1";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		ChangeDirText = "Up_1";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		ChangeDirText = "Down_1";
	}

	HeadRender_->ChangeAnimation(GetHeadAnimationName() + ChangeDirText);
	for (int i = 0; i < HeadAddRender_.size(); i++)
	{
		HeadAddRender_[i]->ChangeAnimation(ChangeDirText);
	}
}
