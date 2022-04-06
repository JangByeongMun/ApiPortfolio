#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>

// Start
void Player::BodyIdleStart()
{
	BodyRender_->ChangeAnimation(BodyAnimationName + "Idle");
}
void Player::BodyMoveStart()
{

}
void Player::HeadIdleStart()
{
	HeadRender_->ChangeAnimation(HeadAnimationName + "Idle");
}
void Player::HeadAttackStart()
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
}
void Player::BodyMoveUpdate()
{
	if (false == IsMoveKey())
	{
		ChangeBodyState(PlayerBodyState::Idle);
		return;
	}

	// ���ÿ� ���� Ű�� �������� �밢������ �����ϼ��ְ�, �׶� ��, �Ʒ� �����̴� �ִϸ��̼��̹Ƿ� else�� �ƴ϶� ���� if�� ����
	float4 MoveDir = float4::ZERO;
	std::string ChangeDirText = "Idle";
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT;
		ChangeDirText = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT;
		ChangeDirText = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir += float4::UP;
		ChangeDirText = "Up";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir += float4::DOWN;
		ChangeDirText = "Down";
	}
	BodyRender_->ChangeAnimation(BodyAnimationName + ChangeDirText);

	// Speed�� �ΰ����� ���ǵ��ġ, 300�� �����̴°ɺ��� ���� ���� ��
	float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_ * 300);
	int Color = MapColImage_->GetImagePixel(NextPos);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_ * 250);
	}
}
void Player::HeadIdleUpdate()
{
	if (true == IsAttackKey())
	{
		ChangeHeadState(PlayerHeadState::Attack);
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
		Shoot(AttackDir * ShotSpeed_ * 350, ProjectileType::PLAYER_BASIC, AttackDir * 30);

		HeadRender_->ChangeAnimation(HeadAnimationName + ChangeDirText + "_2");

		NextAttackTime_ = CurrentAttackTime_ + TearDelay;
		return;
	}

	if (true == HeadRender_->IsEndAnimation())
	{
		HeadRender_->ChangeAnimation(HeadAnimationName + ChangeDirText + "_1");
	}
}