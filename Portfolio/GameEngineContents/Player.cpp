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

#include "ContentsGlobal.h"
#include "Projectile.h"
#include "Bomb.h"
#include "PlayerUI.h"
#include "HPUI.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
	: BodyRender_(nullptr)
	, HeadRender_(nullptr)
	, PlayerCollision(nullptr)
	, MapColImage_(nullptr)
	, BodyAnimationName("Body_")
	, HeadAnimationName("Head_")
	, BlueBodyAnimationName("B_Body_")
	, BlueHeadAnimationName("B_Head_")
	, CurBody_()
	, CurHead_()
	, MoveDir_({ 0, 0 })
	, MaxHp_(3)
	, Damage_(3.5f)
	, AttackSpeed_(2.73f)
	, ShotSpeed_(1.0f)
	, Range_(6.5f)
	, MoveSpeed_(1.0f)
	, Luck_(0)
	, NextAttackTime_(0.0f)
	, CurrentAttackTime_(0.0f)
	, MoneyCount_(0)
	, KeyCount_(0)
	, BombCount_(0)
	, PlayerUI_(nullptr)
{
}
Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	PlayerUI_ = GetLevel()->CreateActor<PlayerUI>();
	PlayerCollision = CreateCollision("PlayerHitBox", { 100, 100 });

	MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	BodyRender_ = CreateRenderer(RenderPivot::CENTER, { 0, 30 });
	BodyRender_->CreateAnimation("001_isaac_left.bmp", "Body_Left", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Right", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Up", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Down", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Idle", 8, 8, 0.1f, false);
	BodyRender_->ChangeAnimation("Body_Idle");
	
	HeadRender_ = CreateRenderer(RenderPivot::CENTER, { 0, -10 });
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Head_Left_1", 2, 2, 0, false);
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Head_Left_2", 2, 3, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Right_1", 2, 2, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Right_2", 2, 3, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Up_1", 4, 4, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Up_2", 4, 5, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Down_1", 0, 0, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Down_2", 0, 1, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Idle", 0, 0, 0, false);
	HeadRender_->ChangeAnimation("Head_Idle");

	// bluebaby 버전 추가
	{
		BodyRender_->CreateAnimation("006_bluebaby_left.bmp", "B_Body_Left", 16, 25, 0.1f, true);
		BodyRender_->CreateAnimation("006_bluebaby.bmp", "B_Body_Right", 16, 25, 0.1f, true);
		BodyRender_->CreateAnimation("006_bluebaby.bmp", "B_Body_Up", 6, 15, 0.1f, true);
		BodyRender_->CreateAnimation("006_bluebaby.bmp", "B_Body_Down", 6, 15, 0.1f, true);
		BodyRender_->CreateAnimation("006_bluebaby.bmp", "B_Body_Idle", 8, 8, 0.1f, false);

		HeadRender_->CreateAnimation("006_bluebaby_left.bmp", "B_Head_Left_1", 2, 2, 0, false);
		HeadRender_->CreateAnimation("006_bluebaby_left.bmp", "B_Head_Left_2", 2, 3, 0.1f, false);
		HeadRender_->CreateAnimation("006_bluebaby.bmp", "B_Head_Right_1", 2, 2, 0, false);
		HeadRender_->CreateAnimation("006_bluebaby.bmp", "B_Head_Right_2", 2, 3, 0.1f, false);
		HeadRender_->CreateAnimation("006_bluebaby.bmp", "B_Head_Up_1", 4, 4, 0, false);
		HeadRender_->CreateAnimation("006_bluebaby.bmp", "B_Head_Up_2", 4, 5, 0.1f, false);
		HeadRender_->CreateAnimation("006_bluebaby.bmp", "B_Head_Down_1", 0, 0, 0, false);
		HeadRender_->CreateAnimation("006_bluebaby.bmp", "B_Head_Down_2", 0, 1, 0.1f, false);
		HeadRender_->CreateAnimation("006_bluebaby.bmp", "B_Head_Idle", 0, 0, 0, false);
	}

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

void Player::LevelChangeStart()
{
	MainPlayer = this;
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
	float4 NextPos_x = GetPosition() + float4(_Value.x, 0);
	float4 NextPos_y = GetPosition() + float4(0, _Value.y);
	int Color = MapColImage_->GetImagePixel(NextPos);
	int Color_x = MapColImage_->GetImagePixel(NextPos_x);
	int Color_y = MapColImage_->GetImagePixel(NextPos_y);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(_Value);
	}
	else if (RGB(0, 0, 0) != Color_x)
	{
		SetMove(float4(_Value.x, 0));
	}
	else if (RGB(0, 0, 0) != Color_y)
	{
		SetMove(float4(0, _Value.y));
	}
}

void Player::GetPlayerInfo()
{
	CharacterType test = SelectedCharacterType;
	switch (SelectedCharacterType)
	{
	case CharacterType::ISAAC:
		MaxHp_ = 3;
		Damage_ = 3.5f;
		AttackSpeed_ = 2.73f;
		ShotSpeed_ = 1;
		Range_ = 6.5f;
		MoveSpeed_ = 1;
		Luck_ = 0;
		MoneyCount_ = 0;
		KeyCount_ = 0;
		BombCount_ = 1;
		break;
	case CharacterType::CAIN:
		MaxHp_ = 2;
		Damage_ = 3.5f;
		AttackSpeed_ = 2.73f;
		ShotSpeed_ = 1;
		Range_ = 4.5f;
		MoveSpeed_ = 1.3f;
		Luck_ = 0;
		MoneyCount_ = 0;
		KeyCount_ = 1;
		BombCount_ = 0;

		MakeHeadAddRenderer("character_003_cainseyepatch.bmp");
		break;
	case CharacterType::MAGDALENE:
		MaxHp_ = 4;
		Damage_ = 3.5f;
		AttackSpeed_ = 2.73f;
		ShotSpeed_ = 1;
		Range_ = 6.5f;
		MoveSpeed_ = 0.85f;
		Luck_ = 0;
		MoneyCount_ = 0;
		KeyCount_ = 0;
		BombCount_ = 0;

		MakeHeadAddRenderer("character_002_maggiesbeautifulgoldenlocks.bmp");
		break;
	case CharacterType::JUDAS:
		MaxHp_ = 1;
		Damage_ = 3.5f;
		AttackSpeed_ = 2.73f;
		ShotSpeed_ = 1;
		Range_ = 6.5f;
		MoveSpeed_ = 1.0f;
		Luck_ = 0;
		MoneyCount_ = 3;
		KeyCount_ = 0;
		BombCount_ = 0;

		MakeHeadAddRenderer("character_004_judasfez.bmp");
		break;
	case CharacterType::BLUEBABY:
		MaxHp_ = 0;
		Damage_ = 3.5f;
		AttackSpeed_ = 2.73f;
		ShotSpeed_ = 1;
		Range_ = 6.5f;
		MoveSpeed_ = 1.1f;
		Luck_ = 0;
		MoneyCount_ = 0;
		KeyCount_ = 0;
		BombCount_ = 0;
		break;
	default:
		break;
	}

	PlayerUI_->Setting();

	ChangeHeadState(PlayerHeadState::Attack);
	ChangeBodyState(PlayerBodyState::Move);
}

void Player::MakeHeadAddRenderer(const std::string& _Name)
{
	GameEngineRenderer* chracterRenderer_ = CreateRenderer(RenderPivot::CENTER, { 0, -8 });
	chracterRenderer_->CreateAnimation(_Name, "Idle", 0, 0, 0, false);
	chracterRenderer_->CreateAnimation(_Name, "Left_1", 6, 6, 0, false);
	chracterRenderer_->CreateAnimation(_Name, "Left_2", 6, 7, 0.1f, false);
	chracterRenderer_->CreateAnimation(_Name, "Right_1", 2, 2, 0, false);
	chracterRenderer_->CreateAnimation(_Name, "Right_2", 2, 3, 0.1f, false);
	chracterRenderer_->CreateAnimation(_Name, "Up_1", 4, 4, 0, false);
	chracterRenderer_->CreateAnimation(_Name, "Up_2", 4, 5, 0.1f, false);
	chracterRenderer_->CreateAnimation(_Name, "Down_1", 0, 0, 0, false);
	chracterRenderer_->CreateAnimation(_Name, "Down_2", 0, 1, 0.1f, false);
	chracterRenderer_->ChangeAnimation("Idle");
	HeadAddRender_.push_back(chracterRenderer_);
}

std::string Player::GetBodyAnimationName()
{
	if (SelectedCharacterType == CharacterType::BLUEBABY)
	{
		return BlueBodyAnimationName;
	}
	else
	{
		return BodyAnimationName;
	}
}

std::string Player::GetHeadAnimationName()
{
	if (SelectedCharacterType == CharacterType::BLUEBABY)
	{
		return BlueHeadAnimationName;
	}
	else
	{
		return HeadAnimationName;
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
		case PlayerHeadState::Move:
			HeadMoveStart();
		default:
			break;
		}

		CurHead_ = _State;
	}
}
void Player::StateUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown("Bomb"))
	{
		PlayerUI_->HpUI_->AddHearts(1, HeartType::SoulHeart);
		PlayerUI_->HpUI_->AddHearts(1, HeartType::BlackHeart);
	}

	switch (CurHead_)
	{
	case PlayerHeadState::Idle:
		HeadIdleUpdate();
		break;
	case PlayerHeadState::Attack:
		HeadAttackUpdate();
		break;
	case PlayerHeadState::Move:
		HeadMoveUpdate();
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