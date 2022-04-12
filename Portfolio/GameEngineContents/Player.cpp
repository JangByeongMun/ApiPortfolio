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
#include "Bomb.h"

Player::Player()
	: Speed_(1)
	, BodyRender_(nullptr)
	, HeadRender_(nullptr)
	, PlayerCollision(nullptr)
	, MapColImage_(nullptr)
	, BodyAnimationName("Body_")
	, HeadAnimationName("Head_")
	, CurBody_()
	, CurHead_()
	, MoveDir_({ 0, 0 })
	, AttackSpeed_(2.73f)
	, ShotSpeed_(1)
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
	BodyRender_->CreateAnimation("001_isaac_left.bmp", "Body_Left", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Right", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Up", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Down", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Idle", 8, 8, 0.1f, false);
	BodyRender_->ChangeAnimation("Body_Idle");
	
	HeadRender_ = CreateRenderer(RenderPivot::CENTER, { 0, 0 });
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Head_Left_1", 2, 2, 0, false);
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Head_Left_2", 2, 3, 0.2f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Right_1", 2, 2, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Right_2", 2, 3, 0.2f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Up_1", 4, 4, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Up_2", 4, 5, 0.2f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Down_1", 0, 0, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Down_2", 0, 1, 0.2f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Idle", 0, 0, 0, false);
	HeadRender_->ChangeAnimation("Head_Idle");

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

	ChangeBodyState(PlayerBodyState::Idle);
	ChangeHeadState(PlayerHeadState::Idle);
}

void Player::Update()
{
	// 상태 관리
	StateUpdate();

	// 충돌 체크
	CollisionCheck();

	if (true == GameEngineInput::GetInst()->IsDown("Bomb"))
	{
		GameEngineActor* BombActor = GetLevel()->CreateActor<Bomb>();
		BombActor->SetPosition(GetPosition());
	}
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

// 벽이 있는지 확인하고 이동하도록하는 함수
void Player::PlayerSetMove(float4 _Value)
{
	float4 NextPos = GetPosition() + _Value;
	int Color = MapColImage_->GetImagePixel(NextPos);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(_Value);
	}
}

bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		return false;
	}

	return true;
}
bool Player::IsAttackKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("AttackLeft") &&
		false == GameEngineInput::GetInst()->IsPress("AttackRight") &&
		false == GameEngineInput::GetInst()->IsPress("AttackUp") &&
		false == GameEngineInput::GetInst()->IsPress("AttackDown"))
	{
		return false;
	}

	return true;
}
void Player::ChangeBodyState(PlayerBodyState _State)
{
	if (CurBody_ != _State)
	{
		switch (_State)
		{
		case PlayerBodyState::Idle:
			BodyIdleStart();
			break;
		case PlayerBodyState::Move:
			BodyMoveStart();
			break;
		default:
			break;
		}

		CurBody_ = _State;
	}
}
void Player::ChangeHeadState(PlayerHeadState _State)
{
	if (CurHead_ != _State)
	{
		switch (_State)
		{
		case PlayerHeadState::Idle:
			HeadIdleStart();
			break;
		case PlayerHeadState::Attack:
			HeadAttackStart();
			break;
		default:
			break;
		}

		CurHead_ = _State;
	}
}
void Player::StateUpdate()
{
	switch (CurHead_)
	{
	case PlayerHeadState::Idle:
		HeadIdleUpdate();
		break;
	case PlayerHeadState::Attack:
		HeadAttackUpdate();
		break;
	default:
		break;
	}

	switch (CurBody_)
	{
	case PlayerBodyState::Idle:
		BodyIdleUpdate();
		break;
	case PlayerBodyState::Move:
		BodyMoveUpdate();
		break;
	default:
		break;
	}
}

void Player::AddItem(ItemType _Type, int _Count)
{
	switch (_Type)
	{
	case ItemType::None:
		break;
	case ItemType::Bomb:
		BombCount_ += _Count;
		break;
	case ItemType::Key:
		KeyCount_ += _Count;
		break;
	case ItemType::Money:
		MoneyCount_ += _Count;
		break;
	case ItemType::Max:
		break;
	default:
		break;
	}
}