#include "KeyItem.h"
#include "Player.h"
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

KeyItem::KeyItem() 
	: Renderer_(nullptr)
	, Type_(KeyType::None)
{
}

KeyItem::~KeyItem() 
{
}

void KeyItem::SetType(KeyType _Type)
{
	Renderer_ = CreateRenderer("pickup_003_key.bmp", RenderPivot::CENTER, {0, 0}, static_cast<int>(ORDER::PLAYER));

	Type_ = _Type;
	switch (Type_)
	{
	case KeyType::None:
		Renderer_->SetIndex(3);
		break;
	case KeyType::Normal:
		Renderer_->SetIndex(0);
		GameEngineSound::SoundPlayOneShotWithVolume("keydrop.wav", 0, 0.1f * Option_SFX);
		break;
	case KeyType::Two:
		Renderer_->SetIndex(2);
		GameEngineSound::SoundPlayOneShotWithVolume("keydrop.wav", 0, 0.1f * Option_SFX);
		break;
	case KeyType::Master:
		Renderer_->SetIndex(1);
		break;
	default:
		break;
	}

	Collision_ = CreateCollision("Item", {60, 60});
}

void KeyItem::Update()
{
	SetObjectMove();

	if (StartTimer_ < 0.2f)
	{
		return;
	}

	/////// Ãæµ¹
	if (true == Collision_->IsUpdate() && true == Collision_->CollisionCheckRect("Player"))
	{
		switch (Type_)
		{
		case KeyType::None:
			break;
		case KeyType::Normal:
			Player::MainPlayer->AddItem(ItemType::Key);
			GameEngineSound::SoundPlayOneShotWithVolume("keypickup.wav", 0, 0.1f * Option_SFX);
			break;
		case KeyType::Two:
			Player::MainPlayer->AddItem(ItemType::KeyTwo);
			GameEngineSound::SoundPlayOneShotWithVolume("keypickup.wav", 0, 0.1f * Option_SFX);
			break;
		case KeyType::Master:
			Player::MainPlayer->AddItem(ItemType::keyMaster);
			GameEngineSound::SoundPlayOneShotWithVolume("golden key.wav", 0, 0.1f * Option_SFX);
			break;
		default:
			break;
		}

		Death();
	}
}