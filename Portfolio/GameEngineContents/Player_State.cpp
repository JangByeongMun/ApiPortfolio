#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

float AcheiveTimer_;

void Player::SetAcheiveRenderer(const std::string& _Name)
{
	AcheiveRender_ = CreateRenderer(_Name);
	AcheiveRender_->SetPivot({0, -30});
}

// Start
void Player::BodyIdleStart()
{
	BodyRender_->ChangeAnimation(GetBodyAnimationName() + "Idle");
}
void Player::BodyMoveStart()
{

}
void Player::BodyAcheiveStart()
{
	BodyRender_->ChangeAnimation("None");
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
void Player::HeadAcheiveStart()
{
	HeadRender_->ChangeAnimation("None");
	int CharacterIndex = static_cast<int>(CharacterType_);
	for (int i = 0; i < AnimRender_.size(); i++)
	{
		if (i == CharacterIndex)
		{
			AnimRender_[i]->On();
			AnimRender_[i]->SetIndex(5);
		}
		else
		{
			AnimRender_[i]->Off();
		}
	}
	for (int i = 0; i < HeadAddRender_.size(); i++)
	{
		HeadAddRender_[i]->Off();
	}
	AcheiveTimer_ = 1.0f;
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

		PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 200);
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
	std::string ChangeDirText = "Idle";
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * 10;
		ChangeDirText = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 10;
		ChangeDirText = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ += float4::UP * GameEngineTime::GetDeltaTime() * 10;
		ChangeDirText = "Up";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 10;
		ChangeDirText = "Down";
	}
	MoveDir_.Limit2D(1.0f);

	BodyRender_->ChangeAnimation(GetBodyAnimationName() + ChangeDirText);

	// MoveSpeed_�� �ΰ����� ���ǵ��ġ, 450�� �����̴°ɺ��� ���� ���� ��
	PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 450);
	
	// �׽�Ʈ�� ī�޶� �̵�
	//GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetScale().Half());
}
void Player::BodyAcheiveUpdate()
{
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
		Shoot(AttackDir * ShotSpeed_ * 500, ProjectileType::PLAYER_BASIC, AttackDir * 30, 1.0f, Damage_);

		HeadRender_->ChangeAnimation(GetHeadAnimationName() + ChangeDirText + "_2");

		NextAttackTime_ = CurrentAttackTime_ + TearDelay;

		// �ΰ����� �Ǽ��縮�� �ִϸ��̼ǵ� ����

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
void Player::HeadAcheiveUpdate()
{
	AcheiveTimer_ -= GameEngineTime::GetDeltaTime();

	if (AcheiveTimer_ <= 0)
	{
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->Off();
		}
		for (int i = 0; i < HeadAddRender_.size(); i++)
		{
			HeadAddRender_[i]->On();
		}
		AcheiveRender_->Death();
		ChangeBodyState(PlayerBodyState::Idle);
		ChangeHeadState(PlayerHeadState::Idle);
	}


	// �ִϸ��̼��� �ٲ���־ �̵��� ����ϹǷ� �̵� ��ũ��Ʈ
	if (false == IsMoveKey())
	{
		MoveDir_ = float4::ZERO;
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * 10;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * 10;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ += float4::UP * GameEngineTime::GetDeltaTime() * 10;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 10;
	}
	MoveDir_.Limit2D(1.0f);

	PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 450);
}
