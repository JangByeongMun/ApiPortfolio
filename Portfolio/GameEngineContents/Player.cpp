#include "Player.h"
#include <Windows.h>

#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>

#include "Projectile.h"

Player::Player()
	: Speed_(1)
	, BodyRender_(nullptr)
	, HeadRender_(nullptr)
	, PlayerCollision(nullptr)
	, MapColImage_(nullptr)
	, MoveAnimationName("Move_")
	, AttackAnimationName("Attack_")
	, CurMove_()
	, CurAttack_()
	, AttackSpeed_(2.73f)
	, NextAttackTime_(0.0f)
	, CurrentAttackTime_(0.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	PlayerCollision = CreateCollision("PlayerHitBox", { 100, 100 });

	MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	BodyRender_ = CreateRenderer(RenderPivot::CENTER, { 0, 30 });
	BodyRender_->CreateAnimation("001_isaac_left.bmp", "Move_Left", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Move_Right", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Move_Up", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Move_Down", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Move_Idle", 8, 8, 0.1f, false);
	BodyRender_->ChangeAnimation("Move_Idle");
	
	HeadRender_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 });
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Attack_Left_1", 2, 2, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Attack_Left_2", 2, 3, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Right_1", 2, 2, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Right_2", 2, 3, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Up_1", 4, 4, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Up_2", 4, 5, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Down_1", 0, 0, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Down_2", 0, 1, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Idle", 0, 0, 0.1f, false);
	HeadRender_->ChangeAnimation("Attack_Idle");

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("AttackLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("AttackRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("AttackUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("AttackDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Bomb", 'E');
	}
}


void Player::Update()
{
	// 움직임 관리
	{
		float4 MoveDir = float4::ZERO;
		PlayerMoveDir CheckMove = PlayerMoveDir::Idle;
		std::string ChangeDirText = "Idle";
		
		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			MoveDir += float4::LEFT;
			CheckMove = PlayerMoveDir::Left;
			ChangeDirText = "Left";
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			MoveDir += float4::RIGHT;
			CheckMove = PlayerMoveDir::Right;
			ChangeDirText = "Right";
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			MoveDir += float4::UP;
			CheckMove = PlayerMoveDir::Up;
			ChangeDirText = "Up";
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			MoveDir += float4::DOWN;
			CheckMove = PlayerMoveDir::Down;
			ChangeDirText = "Down";
		}

		if (CheckMove != CurMove_)
		{
			BodyRender_->ChangeAnimation(MoveAnimationName + ChangeDirText);
			CurMove_ = CheckMove;
		}

		// Speed는 인게임의 스피드수치, 300은 움직이는걸보고 대충 맞춘 값
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_ * 300);

		int Color = MapColImage_->GetImagePixel(NextPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_ * 300);
		}
	}

	// 공격 입력
	{
		AttackCheck();
	}

	// 충돌 체크
	{
		CollisionCheck();
	}
}

void Player::Render()
{
}

void Player::CollisionCheck()
{
	std::vector<GameEngineCollision*> ColVec;

	if (true == PlayerCollision->CollisionResult("Wall", ColVec, CollisionType::Rect, CollisionType::Rect))
	{
		for (int i = 0; i < ColVec.size(); i++)
		{
			ColVec[i]->Death();
		}
	}
}

void Player::AttackCheck()
{
	CurrentAttackTime_ += GameEngineTime::GetDeltaTime();
	PlayerAttackDir CheckAttack = PlayerAttackDir::Idle;
	std::string ChangeDirTextSuccess = "Idle";
	std::string ChangeDirTextFail = "Idle";
	float4 MoveDir = float4::ZERO;
	float TearDelay = 1.0f;

	if (true == GameEngineInput::GetInst()->IsPress("AttackLeft"))
	{
		MoveDir = float4::LEFT;
		CheckAttack = PlayerAttackDir::Left;
		ChangeDirTextFail = "Left_1";
		ChangeDirTextSuccess = "Left_2";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackRight"))
	{
		MoveDir = float4::RIGHT;
		CheckAttack = PlayerAttackDir::Right;
		ChangeDirTextFail = "Right_1";
		ChangeDirTextSuccess = "Right_2";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackUp"))
	{
		MoveDir = float4::UP;
		CheckAttack = PlayerAttackDir::Up;
		ChangeDirTextFail = "Up_1";
		ChangeDirTextSuccess = "Up_2";
	}
	else if (true == GameEngineInput::GetInst()->IsPress("AttackDown"))
	{
		MoveDir = float4::DOWN;
		CheckAttack = PlayerAttackDir::Down;
		ChangeDirTextFail = "Down_1";
		ChangeDirTextSuccess = "Down_2";
	}
	else if (PlayerAttackDir::Idle != CurAttack_) // 이전 프레임에선 공격하고있었으나 지금 멈췄을때
	{

	}

	if (NextAttackTime_ <= CurrentAttackTime_ && false == MoveDir.IsZero2D())
	{
		Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetVector(MoveDir);
		Ptr->SetSpeed(200.0f);

		HeadRender_->ChangeAnimation(AttackAnimationName + ChangeDirTextSuccess);
		CurAttack_ = CheckAttack;

		NextAttackTime_ = CurrentAttackTime_ + TearDelay;
		return;
	}
	
	if (CurrentAttackTime_ >= NextAttackTime_ - TearDelay + 0.2f)
	{
		HeadRender_->ChangeAnimation(AttackAnimationName + ChangeDirTextFail);
		CurAttack_ = CheckAttack;
	}
}
