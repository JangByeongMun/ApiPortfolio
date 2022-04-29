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
#include "RandomRoomManager.h"
#include "RoomActor.h"
#include "Door.h"
#include "PlayLevel.h"
#include "PlayerHP.h"
#include "EnterBossRoom.h"
#include "Trapdoor.h"
#include "KeyItem.h"
#include "BatteryItem.h"
#include "ActiveUI.h"
#include "BoxItem.h"
#include "HeartItem.h"
#include "BlackHeartEffect.h"
#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
	: BodyRender_(nullptr)
	, HeadRender_(nullptr)
	, PlayerCollision_(nullptr)
	, MapColImage_(nullptr)
	, BodyAnimationName("Body_")
	, HeadAnimationName("Head_")
	, BlueBodyAnimationName("B_Body_")
	, BlueHeadAnimationName("B_Head_")
	, CurBody_()
	, CurHead_()
	, MoveDir_({ 0, 0 })
	, IsDead_(false)
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
	, IsMasterKey_(false)
	, PlayerUI_(nullptr)
	, HavingAccessory_(AccessoryType::None)
	, ActiveType_(ActiveType::Default)
	, MaxGaze_(0)
	, CurrentGaze_(0)
	, IsUsingActive(false)
	, AcheiveItemRender_(nullptr)
	, CharacterType_(CharacterType::ISAAC)
	, RoomPos_({0, 0})
	, InvincibilityTimer_(0)
	, InvisibleTimer_(0)
{
}
Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	PlayerUI_ = GetLevel()->CreateActor<PlayerUI>();
	PlayerCollision_ = CreateCollision("Player", { 60, 65 });

	MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	{
		AnimRender_.push_back(CreateRenderer("001_isaac_Anim.bmp", RenderPivot::CENTER, {0, 0}));
		AnimRender_.push_back(CreateRenderer("003_cain_Anim.bmp", RenderPivot::CENTER, {0, 0}));
		AnimRender_.push_back(CreateRenderer("002_magdalene_Anim.bmp", RenderPivot::CENTER, {0, 0}));
		AnimRender_.push_back(CreateRenderer("004_judas_Anim.bmp", RenderPivot::CENTER, {0, 0}));
		AnimRender_.push_back(CreateRenderer("006_bluebaby_Anim.bmp", RenderPivot::CENTER, {0, 0}));

		for (int i = 0; i < AnimRender_.size(); i++)
		{
			AnimRender_[i]->Off();
		}
	}

	BodyRender_ = CreateRenderer(static_cast<int>(ORDER::BACKPLAYER), RenderPivot::CENTER, { 0, 30 });
	BodyRender_->CreateAnimation("001_isaac_left.bmp", "Body_Left", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Right", 16, 25, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Up", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Down", 6, 15, 0.1f, true);
	BodyRender_->CreateAnimation("001_isaac.bmp", "Body_Idle", 8, 8, 0.1f, false);
	BodyRender_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
	BodyRender_->ChangeAnimation("Body_Idle");
	
	HeadRender_ = CreateRenderer(static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0, -10 });
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Head_Left_1", 2, 2, 0, false);
	HeadRender_->CreateAnimation("001_isaac_left.bmp", "Head_Left_2", 2, 3, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Right_1", 2, 2, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Right_2", 2, 3, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Up_1", 4, 4, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Up_2", 4, 5, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Down_1", 0, 0, 0, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Down_2", 0, 1, 0.1f, false);
	HeadRender_->CreateAnimation("001_isaac.bmp", "Head_Idle", 0, 0, 0, false);
	HeadRender_->CreateAnimation("None.bmp", "None", 0, 0, 0, false);
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
		GameEngineInput::GetInst()->CreateKey("SpaceBar", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Test1", 'R');
		GameEngineInput::GetInst()->CreateKey("Test2", 'T');
	}

	ChangeBodyState(PlayerBodyState::Idle);
	ChangeHeadState(PlayerHeadState::Idle);
}

void Player::Update()
{
	// 시간멈췄을때 작동중지
	if (true == GameEngineTime::IsPause())
	{
		return;
	}

	if (GameEngine::CurrentLevel() != GameEngine::GetInst().FindLevel("Play"))
	{
		return;
	}

	// 상태 관리
	StateUpdate();

	if (true == GameEngineInput::GetInst()->IsDown("Bomb"))
	{
		if (BombCount_ > 0)
		{
			GameEngineActor* BombActor = GetLevel()->CreateActor<Bomb>();
			BombActor->SetPosition(GetPosition());
			MinusItem(ItemType::Bomb, 1);

			GameEngineSound::SoundPlayOneShotWithVolume("fetus land.wav", 0, 0.02f * Option_SFX);
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		UseActive();
		float4 CurrentRoomPos = RandomRoomManager::GetInst()->FindRoom(Player::MainPlayer->GetCurrentRoomPos())->GetPosition();
		GetLevel()->CreateActor<BlackHeartEffect>()->SetPosition(CurrentRoomPos);
	}

	if (true == GameEngineInput::GetInst()->IsDown("Test1"))
	{
		AddGaze(100);
		AddItem(ItemType::KeyTwo);
		AddItem(ItemType::BombTwo);
		PlayerUI_->SetItemUI();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Test2"))
	{
		{
			BoxItem* TmpBox = GetLevel()->CreateActor<BoxItem>();
			TmpBox->SetPosition(GetPosition());
			TmpBox->SetType(BoxType::Gold);
		}
		
		{
			HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
			TmpHeart->SetPosition(GetPosition() + float4(-100, 0));
			TmpHeart->Setting(HeartType::Black);
		}

		{
			HeartItem* TmpHeart = GetLevel()->CreateActor<HeartItem>();
			TmpHeart->SetPosition(GetPosition() + float4(100, 0));
			TmpHeart->Setting(HeartType::Red);
		}
	}

	// 무적시간 구현
	if (InvincibilityTimer_ > 0.0f)
	{
		InvincibilityTimer_ -= GameEngineTime::GetDeltaTime();
		InvisibleTimer_ += GameEngineTime::GetDeltaTime();

		if (InvisibleTimer_ >= 0.2f)
		{
			InvisibleTimer_ = 0.0f;
			BodyRender_->SetAlpha(255);
			HeadRender_->SetAlpha(255);
		}
		else if (InvisibleTimer_ >= 0.1f)
		{
			BodyRender_->SetAlpha(0);
			HeadRender_->SetAlpha(0);
		}

		if (InvincibilityTimer_ <= 0.0f)
		{
			InvincibilityTimer_ = 0.0f;
			InvisibleTimer_ = 0.0f;
			BodyRender_->SetAlpha(255);
			HeadRender_->SetAlpha(255);
		}
	}
}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Player::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (
		_NextLevel == GameEngine::GetInst().FindLevel("Ending") ||
		_NextLevel == GameEngine::GetInst().FindLevel("Menu") ||
		_NextLevel == GameEngine::GetInst().FindLevel("Title")
		)
	{
		NextLevelOff();
		PlayerUI_->NextLevelOff();
		GetPlayerHP()->NextLevelOff();
		MainPlayer = nullptr;
	}
	else
	{
		NextLevelOn();
		SetRoom({ 0, 0 });
		PlayerUI_->NextLevelOn();
		GetPlayerHP()->NextLevelOn();
		SetPosition({ 3000, 3000 });
	}
}

// 벽이 있는지 확인하고 이동하도록하는 함수
void Player::PlayerSetMove(const float4& _Value)
{
	if (true == CanMove(_Value))
	{
		SetMove(_Value);
	}
	else if (true == CanMove(float4(_Value.x, 0)))
	{
		SetMove(float4(_Value.x, 0));
	}
	else if (true == CanMove(float4(0, _Value.y)))
	{
		SetMove(float4(0, _Value.y));
	}
}

bool Player::CanMove(const float4& _Value)
{
	// 룸마다 크기는 같으므로 보정치를 줘서 어떤룸에서도 똑같은 위치만큼만 이동할수있도록
	RoomActor* FindRoom = RandomRoomManager::GetInst()->FindRoom(RoomPos_);
	float4 AddPivot = FindRoom->GetPosition() - GameEngineWindow::GetScale().Half();
	int Color = MapColImage_->GetImagePixel(GetPosition() + _Value - AddPivot);

	if (
		RGB(0, 0, 0) != Color &&
		false == PlayerCollision_->NextPosCollisionCheckRect("Stone", _Value) &&
		false == PlayerCollision_->NextPosCollisionCheckRect("Wall", _Value) &&
		false == PlayerCollision_->NextPosCollisionCheckRect("Poop", _Value)
		)
	{
		return true;
	}

	return false;
}

void Player::SetPlayerInfo()
{
	CharacterType_ = SelectedCharacterType;
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
		Damage_ = 4.2f;
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

		SetActiveType(ActiveType::Item045);
		MakeHeadAddRenderer("character_002_maggiesbeautifulgoldenlocks.bmp");
		break;
	case CharacterType::JUDAS:
		MaxHp_ = 1;
		Damage_ = 4.73f;
		AttackSpeed_ = 2.73f;
		ShotSpeed_ = 1;
		Range_ = 6.5f;
		MoveSpeed_ = 1.0f;
		Luck_ = 0;
		MoneyCount_ = 3;
		KeyCount_ = 0;
		BombCount_ = 0;

		SetActiveType(ActiveType::Item034);
		MakeHeadAddRenderer("character_004_judasfez.bmp");
		break;
	case CharacterType::BLUEBABY:
		MaxHp_ = 0;
		Damage_ = 3.7f;
		AttackSpeed_ = 2.73f;
		ShotSpeed_ = 1;
		Range_ = 6.5f;
		MoveSpeed_ = 1.1f;
		Luck_ = 0;
		MoneyCount_ = 0;
		KeyCount_ = 0;
		BombCount_ = 0;

		SetActiveType(ActiveType::Item036);
		break;
	default:
		break;
	}

	PlayerUI_->Setting();
	if (SelectedCharacterType == CharacterType::BLUEBABY)
	{
		GetPlayerHP()->AddHearts(HeartData::SoulHeart, false);
		GetPlayerHP()->AddHearts(HeartData::SoulHeart, false);
		GetPlayerHP()->AddHearts(HeartData::SoulHeart, false);
	}

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
		case PlayerBodyState::Acheive:
			BodyAcheiveStart();
			break;
		case PlayerBodyState::Hitted:
			BodyHittedStart();
			break;
		case PlayerBodyState::Dead:
			BodyDeadStart();
			break;
		case PlayerBodyState::TrapDoor:
			BodyTrapdoorStart();
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
			break;
		case PlayerHeadState::Acheive:
			HeadAcheiveStart();
			break;
		case PlayerHeadState::Hitted:
			HeadHittedStart();
			break;
		case PlayerHeadState::Dead:
			HeadDeadStart();
			break;
		case PlayerHeadState::TrapDoor:
			HeadTrapdoorStart();
			break;
		default:
			break;
		}

		CurHead_ = _State;
	}
}
void Player::StateUpdate()
{
	switch (CurBody_)
	{
	case PlayerBodyState::Idle:
		BodyIdleUpdate();
		break;
	case PlayerBodyState::Move:
		BodyMoveUpdate();
		break;
	case PlayerBodyState::Acheive:
		BodyAcheiveUpdate();
		break;
	case PlayerBodyState::Hitted:
		BodyHittedUpdate();
		break;
	case PlayerBodyState::Dead:
		BodyDeadUpdate();
		break;
	case PlayerBodyState::TrapDoor:
		BodyTrapdoorUpdate();
		break;
	default:
		break;
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
	case PlayerHeadState::Acheive:
		HeadAcheiveUpdate();
		break;
	case PlayerHeadState::Hitted:
		HeadHittedUpdate();
		break;
	case PlayerHeadState::Dead:
		HeadDeadUpdate();
		break;
	case PlayerHeadState::TrapDoor:
		HeadTrapdoorUpdate();
		break;
	default:
		break;
	}

	CurrentAttackTime_ += GameEngineTime::GetDeltaTime();
}

void Player::AddItem(ItemType _Type)
{
	switch (_Type)
	{
	case ItemType::None:
		break;
	case ItemType::Bomb:
		BombCount_ += 1;
		if (BombCount_ >= 99)
		{
			BombCount_ = 99;
		}
		break;
	case ItemType::BombTwo:
		BombCount_ += 2;
		if (BombCount_ >= 99)
		{
			BombCount_ = 99;
		}
		break;
	case ItemType::Key:
		KeyCount_ += 1;
		if (KeyCount_ >= 99)
		{
			KeyCount_ = 99;
		}
		break;
	case ItemType::KeyTwo:
		KeyCount_ += 2;
		if (KeyCount_ >= 99)
		{
			KeyCount_ = 99;
		}
		break;
	case ItemType::keyMaster:
		IsMasterKey_ = true;
		break;
	case ItemType::Money:
		MoneyCount_ += 1;
		if (MoneyCount_ >= 99)
		{
			MoneyCount_ = 99;
		}
		break;
	case ItemType::MoneyBlack:
		MoneyCount_ += 5;
		if (MoneyCount_ >= 99)
		{
			MoneyCount_ = 99;
		}
		break;
	case ItemType::MoneySilver:
		MoneyCount_ += 10;
		if (MoneyCount_ >= 99)
		{
			MoneyCount_ = 99;
		}
		break;
	case ItemType::Battery:
		CurrentGaze_ = MaxGaze_;
		break;
	case ItemType::Max:
		break;
	default:
		break;
	}

	PlayerUI_->SetItemUI();
}

bool Player::MinusItem(ItemType _Type, int _Value)
{
	// 양수를 넣는다고 생각했는데 음수를 받았을때 양수로 바꾼다음 빼주도록
	if (_Value < 0)
	{
		_Value *= -1;
	}

	switch (_Type)
	{
	case ItemType::Bomb:
		if (BombCount_ >= _Value)
		{
			BombCount_ -= _Value;
		}
		else
		{
			return false;
		}
		break;
	case ItemType::Key:
		if (true == IsMasterKey_)
		{
			break;
		}
		else if (KeyCount_ >= _Value)
		{
			KeyCount_ -= _Value;
		}
		else
		{
			return false;
		}
		break;
	case ItemType::Money:
		if (MoneyCount_ >= _Value)
		{
			MoneyCount_ -= _Value;
		}
		else
		{
			return false;
		}
		break;
	default:
		break;
	}

	PlayerUI_->SetItemUI();
	return true;
}

void Player::BlackHeartDestroy()
{
	RandomRoomManager::GetInst()->FindRoom(RoomPos_)->AllMonsterAttack(40);
}

PlayerHP* Player::GetPlayerHP()
{
	return PlayerUI_->PlayerHP_;
}

ActiveUI* Player::GetActiveUI()
{
	return PlayerUI_->ActiveUI_;
}

void Player::SetAccessory(AccessoryType _Type)
{
	HavingAccessory_ = _Type;
	PlayerUI_->SetAccessoryUI();
}

void Player::SetRoom(float4 _Pos)
{
	RoomPos_ = _Pos;
}

void Player::ChangeRoom(DoorDir _Dir)
{
	float4 GoDir;
	DoorDir otherSide = DoorDir::Down;
	switch (_Dir)
	{
	case DoorDir::Up:
		GoDir = {0, -1};
		otherSide = DoorDir::Down;
		break;
	case DoorDir::Down:
		GoDir = {0, 1};
		otherSide = DoorDir::Up;
		break;
	case DoorDir::Left:
		GoDir = {-1, 0};
		otherSide = DoorDir::Right;
		break;
	case DoorDir::Right:
		GoDir = {1, 0};
		otherSide = DoorDir::Left;
		break;
	default:
		break;
	}
	RoomPos_ += GoDir;

	RoomActor* FindRoom = RandomRoomManager::GetInst()->FindRoom(RoomPos_);

	switch (_Dir)
	{
	case DoorDir::Up:
		SetPosition(FindRoom->FindDoor(otherSide)->GetPosition() + GoDir * 86);
		break;
	case DoorDir::Down:
		SetPosition(FindRoom->FindDoor(otherSide)->GetPosition() + GoDir * 35);
		break;
	case DoorDir::Left:
		SetPosition(FindRoom->FindDoor(otherSide)->GetPosition() + GoDir * 65);
		break;
	case DoorDir::Right:
		SetPosition(FindRoom->FindDoor(otherSide)->GetPosition() + GoDir * 65);
		break;
	default:
		break;
	}
	// 보스방 들어갈때 멈추고 보스입장 애니메이션
	if (0 != FindRoom->GetBossCount())
	{
		GetLevel()->SetCameraPos(FindRoom->GetPosition() - GameEngineWindow::GetScale().Half());
		
		EnterBossRoom* TmpActor = GetLevel()->CreateActor<EnterBossRoom>();
		TmpActor->SetPosition(FindRoom->GetPosition());
		TmpActor->Setting();

		GameEngineTime::Pause();
	}
	else
	{
		PlayLevel* TmpPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
		TmpPlayLevel->CameraLerp(GetLevel()->GetCameraPos(), FindRoom->GetPosition() - GameEngineWindow::GetScale().Half());
	}

	if (false == PlayLevel::GetDebugMode())
	{
		if (0 != FindRoom->GetMonsterCount() || 0 != FindRoom->GetBossCount())
		{
			FindRoom->CloseAllDoor();
			GameEngineSound::SoundPlayOneShotWithVolume("door heavy close.wav", 0, 0.015f * Option_SFX);
		}
	}

	// 보스를 잡은후의 보스방이면 TrapDoor가 있는데 방에 들어가자마자 이동하는걸 막기위해 닫아놨다가 나중에 열리도록
	if (nullptr != FindRoom->GetTrapdoor())
	{
		FindRoom->GetTrapdoor()->TurnOn(false);
	}

	PlayerUI_->UpdateMiniMap(GoDir);

	// 액티브 스킬 사용중이였다면 끄기
	if (true == IsUsingActive)
	{
		IsUsingActive = false;
		if (ActiveType_ == ActiveType::Item034)
		{
			Damage_ -= 2;
		}
	}
}
