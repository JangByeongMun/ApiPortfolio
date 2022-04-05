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
	: Speed_(300.0f)
	, BodyRender_(nullptr)
	, HeadRender_(nullptr)
	, PlayerCollision(nullptr)
	, MapColImage_(nullptr)
	, MoveAnimationName("Move_")
	, AttackAnimationName("Attack_")
	, CurMove_()
	, CurAttack_()
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
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Attack_Left", 2, 3, 0.1f, true);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Right", 2, 3, 0.1f, true);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Up", 4, 5, 0.1f, true);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Attack_Down", 0, 1, 0.1f, true);
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

		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos;

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	// 공격 입력
	{
		PlayerAttackDir CheckAttack = PlayerAttackDir::Idle;
		std::string ChangeDirText = "Idle";

		if (true == GameEngineInput::GetInst()->IsPress("AttackLeft"))
		{
			Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
			Ptr->SetPosition(GetPosition());
			Ptr->SetVector(float4::LEFT);
			Ptr->SetSpeed(200.0f);

			CheckAttack = PlayerAttackDir::Left;
			ChangeDirText = "Left";
		}
		else if (true == GameEngineInput::GetInst()->IsPress("AttackRight"))
		{
			Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
			Ptr->SetPosition(GetPosition());
			Ptr->SetVector(float4::RIGHT);
			Ptr->SetSpeed(200.0f);

			CheckAttack = PlayerAttackDir::Right;
			ChangeDirText = "Right";
		}
		else if (true == GameEngineInput::GetInst()->IsPress("AttackUp"))
		{
			Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
			Ptr->SetPosition(GetPosition());
			Ptr->SetVector(float4::UP);
			Ptr->SetSpeed(200.0f);

			CheckAttack = PlayerAttackDir::Up;
			ChangeDirText = "Up";
		}
		else if (true == GameEngineInput::GetInst()->IsPress("AttackDown"))
		{
			Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
			Ptr->SetPosition(GetPosition());
			Ptr->SetVector(float4::DOWN);
			Ptr->SetSpeed(200.0f);

			CheckAttack = PlayerAttackDir::Down;
			ChangeDirText = "Down";
		}
		else if (PlayerAttackDir::Idle != CurAttack_) // 이전 프레임에선 공격하고있었으나 지금 멈췄을때
		{

		}

		if (CheckAttack != CurAttack_)
		{
			HeadRender_->ChangeAnimation(AttackAnimationName + ChangeDirText);
			CurAttack_ = CheckAttack;
		}
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