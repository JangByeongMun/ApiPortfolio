#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include "DeadReasonUI.h"
#include "PlayLevel.h"
#include <GameEngine/GameEngine.h>

float AnimTimer_;

void Player::SetAcheiveRenderer(const std::string& _Name)
{
	AcheiveItemRender_ = CreateRenderer(_Name, static_cast<int>(ORDER::BACKUI));
	AcheiveItemRender_->SetPivot({0, -30});
	AcheiveItemRender_->Death(1.0f);
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
void Player::BodyHittedStart()
{
	BodyRender_->ChangeAnimation("None");
}
void Player::BodyDeadStart()
{
	BodyRender_->ChangeAnimation("None");
}
void Player::BodyTrapdoorStart()
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
	AnimTimer_ = 0.0f;
}
void Player::HeadHittedStart()
{
	HeadRender_->ChangeAnimation("None");
	int CharacterIndex = static_cast<int>(CharacterType_);
	for (int i = 0; i < AnimRender_.size(); i++)
	{
		if (i == CharacterIndex)
		{
			AnimRender_[i]->On();
			AnimRender_[i]->SetIndex(6);
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
	AnimTimer_ = 0.2f;
	InvincibilityTimer_ = 1.5f;
}
void Player::HeadDeadStart()
{
	HeadRender_->ChangeAnimation("None");
	int CharacterIndex = static_cast<int>(CharacterType_);
	for (int i = 0; i < AnimRender_.size(); i++)
	{
		if (i == CharacterIndex)
		{
			AnimRender_[i]->On();
			AnimRender_[i]->SetIndex(0);
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
	AnimTimer_ = 0.0f;
}
void Player::HeadTrapdoorStart()
{
	HeadRender_->ChangeAnimation("None");
	MoveDir_ = float4::ZERO;
	int CharacterIndex = static_cast<int>(CharacterType_);
	for (int i = 0; i < AnimRender_.size(); i++)
	{
		if (i == CharacterIndex)
		{
			AnimRender_[i]->On();
			AnimRender_[i]->SetIndex(4);
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
	AnimTimer_ = 0.0f;
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

		PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 400);
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
	// MoveSpeed_는 인게임의 스피드수치, 400은 움직이는걸보고 대충 맞춘 값
	PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 400);
}
void Player::BodyAcheiveUpdate()
{
}
void Player::BodyHittedUpdate()
{
}
void Player::BodyDeadUpdate()
{
}
void Player::BodyTrapdoorUpdate()
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
	float4 OtherDir = float4::ZERO;
	float TearDelay = 1 / AttackSpeed_;

	if (true == GameEngineInput::GetInst()->IsPress("AttackLeft"))
	{
		AttackDir = float4::LEFT;
		OtherDir = float4::DOWN;
		ChangeDirText = "Left";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackRight"))
	{
		AttackDir = float4::RIGHT;
		OtherDir = float4::DOWN;
		ChangeDirText = "Right";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackUp"))
	{
		AttackDir = float4::UP;
		OtherDir = float4::RIGHT;
		ChangeDirText = "Up";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackDown"))
	{
		AttackDir = float4::DOWN;
		OtherDir = float4::RIGHT;
		ChangeDirText = "Down";
	}

	

	if (NextAttackTime_ <= CurrentAttackTime_ && false == AttackDir.IsZero2D())
	{
		if (true == PlayLevel::GetDebugMode1or2())
		{
			Shoot(AttackDir * ShotSpeed_ * 500, ProjectileType::PLAYER_BASIC, AttackDir * 30, 1.0f, 100);
		}
		else
		{
			if (true == Have245_)
			{
				Shoot(AttackDir * ShotSpeed_ * 500 + MoveDir_ * 150, ProjectileType::PLAYER_BASIC, AttackDir * 30 + OtherDir * 15, 1.0f, Damage_ + AddDamageTo109_);
				Shoot(AttackDir * ShotSpeed_ * 500 + MoveDir_ * 150, ProjectileType::PLAYER_BASIC, AttackDir * 30 - OtherDir * 15, 1.0f, Damage_ + AddDamageTo109_);
			}
			else
			{
				Shoot(AttackDir * ShotSpeed_ * 500 + MoveDir_ * 150, ProjectileType::PLAYER_BASIC, AttackDir * 30, 1.0f, Damage_ + AddDamageTo109_);
			}
		}

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
void Player::HeadAcheiveUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ >= 1.0f)
	{
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->Off();
		}
		for (int i = 0; i < HeadAddRender_.size(); i++)
		{
			HeadAddRender_[i]->On();
		}
		AcheiveItemRender_->Death();
		ChangeBodyState(PlayerBodyState::Idle);
		ChangeHeadState(PlayerHeadState::Idle);
	}


	// 애니메이션은 바뀌어있어도 이동은 계속하므로 이동 스크립트
	if (false == IsMoveKey())
	{
		MoveDir_ += -MoveDir_ * GameEngineTime::GetDeltaTime() * 10;
	}
	else
	{
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
	}
	MoveDir_.Limit2D(1.0f);

	PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 400);
}
void Player::HeadHittedUpdate()
{
	AnimTimer_ -= GameEngineTime::GetDeltaTime();

	if (AnimTimer_ <= 0)
	{
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->Off();
		}
		for (int i = 0; i < HeadAddRender_.size(); i++)
		{
			HeadAddRender_[i]->On();
		}

		ChangeBodyState(PlayerBodyState::Idle);
		ChangeHeadState(PlayerHeadState::Idle);
	}

	// 애니메이션은 바뀌어있어도 이동은 계속하므로 이동 스크립트
	if (false == IsMoveKey())
	{
		MoveDir_ += -MoveDir_ * GameEngineTime::GetDeltaTime() * 10;
	}
	else
	{
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
	}
	MoveDir_.Limit2D(1.0f);

	PlayerSetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * MoveSpeed_ * 400);
}
void Player::HeadDeadUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ >= 0.3f)
	{
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->SetIndex(6);
		}
	}

	if (AnimTimer_ >= 0.6f)
	{
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->SetIndex(3);
		}
	}

	if (AnimTimer_ >= 1.0f && false == IsDead_)
	{
		IsDead_ = true;
		GetLevel()->CreateActor<DeadReasonUI>();

		PlayLevel* TmpLevel = dynamic_cast<PlayLevel*>(GetLevel());
		if (TmpLevel != nullptr)
		{
			TmpLevel->StopBGM();
		}

		GameEngineTime::Pause();
	}
}
void Player::HeadTrapdoorUpdate()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	for (int i = 0; i < AnimRender_.size(); i++)
	{
		AnimRender_[i]->SetPivot({0, -100});
	}

	if (AnimTimer_ >= 0.3f)
	{
		float4 LerpPos = float4::Lerp({ 0, -100 }, {0, -80}, (AnimTimer_-0.3f) * 5.0f);
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->SetIndex(8);
			AnimRender_[i]->SetPivot(LerpPos);
		}
	}

	if (AnimTimer_ >= 0.5f)
	{
		float4 LerpPos = float4::Lerp({ 0, -80 }, { 0, 0 }, (AnimTimer_ - 0.5f) * 4.0f);
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->SetIndex(9);
			AnimRender_[i]->SetPivot(LerpPos);
		}
	}

	if (AnimTimer_ >= 0.7f)
	{
		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->Off();
		}
	}

	if (AnimTimer_ >= 0.9f)
	{
		for (int i = 0; i < HeadAddRender_.size(); i++)
		{
			HeadAddRender_[i]->On();
		}
		ChangeBodyState(PlayerBodyState::Idle);
		ChangeHeadState(PlayerHeadState::Idle);
		GameEngine::GetInst().ChangeLevel("Loading");
	}
}
