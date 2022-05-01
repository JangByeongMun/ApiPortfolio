#include "BoomFly.h"
#include <GameEngine/GameEngineImageManager.h>
#include "RandomRoomManager.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "RoomActor.h"
#include "Bomb.h"
#include "ShopKeeper.h"
#include <GameEngineBase/GameEngineSound.h>
#include "PlayLevel.h"
#include "Stone.h"
#include "Player.h"
#include "PlayerUI.h"
#include "PlayerHP.h"	
#include "Poop.h"
#include "Fire.h"

BoomFly::BoomFly() 
	: Type_(BoomFlyType::Normal)
	, MoveDir_(1, 1)
{
}

BoomFly::~BoomFly() 
{
}

void BoomFly::Setting(BoomFlyType _Type)
{
	Type_ = _Type;
	Collision_ = CreateCollision("Monster", { 50, 50 });
	Renderer_ = CreateRenderer(static_cast<int>(ORDER::PLAYER));
	switch (_Type)
	{
	case BoomFlyType::Normal:
		Renderer_->CreateAnimation("monster_096_boomfly.bmp", "Idle", 0, 1, 0.1f, true);
		break;
	case BoomFlyType::Red:
		Renderer_->CreateAnimation("monster_101_redboomfly.bmp", "Idle", 0, 1, 0.1f, true);
		break;
	default:
		break;
	}

	Renderer_->ChangeAnimation("Idle");
	SetHP(20);
	SetMoveSpeed(100.0f);
}

void BoomFly::MonsterUpdate()
{
	MoveZigZag(MoveDir_ * MoveSpeed_ * GameEngineTime::GetDeltaTime());
}

void BoomFly::MonsterDeath()
{
	switch (Type_)
	{
	case BoomFlyType::Normal:
	{
		//Boom();
		break;
	}
	case BoomFlyType::Red:
	{
		Shoot({ 300, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 200, 200 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -200, 200 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -300, 0 }, ProjectileType::ENEMY_BASIC);
		Shoot({ -200, -200 }, ProjectileType::ENEMY_BASIC);
		Shoot({ 200, -200 }, ProjectileType::ENEMY_BASIC);
		break;
	}
	default:
		break;
	}
}

void BoomFly::MoveZigZag(float4 _Value)
{
	GameEngineImage* MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");
	float4 AddPivot = Room_->GetPosition() - GameEngineWindow::GetScale().Half();

	// x축이나 y축으로 더이상 갈수없을경우 x나 y중 한군데를 제외하고 이동
	float4 NextPos = GetPosition() + _Value;
	float4 NextPos_x = GetPosition() + float4(_Value.x, _Value.y * -1);
	float4 NextPos_y = GetPosition() + float4(_Value.x * -1, _Value.y);
	int Color = MapColImage_->GetImagePixel(NextPos - AddPivot);
	int Color_x = MapColImage_->GetImagePixel(NextPos_x - AddPivot);
	int Color_y = MapColImage_->GetImagePixel(NextPos_y - AddPivot);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(_Value);
	}
	else if (RGB(0, 0, 0) != Color_x)
	{
		SetMove(float4(_Value.x, 0));
		MoveDir_ = float4(MoveDir_.x, MoveDir_.y * -1);
	}
	else if (RGB(0, 0, 0) != Color_y)
	{
		SetMove(float4(0, _Value.y));
		MoveDir_ = float4(MoveDir_.x * -1, MoveDir_.y);
	}
}

void BoomFly::Boom()
{
	// 폭발 이펙트 생성
	{
		GameEngineRenderer* Renderer = CreateRenderer("effect_029_explosion2.bmp", static_cast<int>(ORDER::UI));
		Renderer->SetAlpha(100);
		Renderer->SetPivot({ 0, -100 });
		Renderer->Death(0.35f);
	}

	{
		GameEngineRenderer* Renderer = CreateRenderer(static_cast<int>(ORDER::UI), RenderPivot::CENTER);
		Renderer->CreateAnimation("effect_029_explosion.bmp", "effect_029_explosion", 0, 11, 0.05f, false);
		Renderer->ChangeAnimation("effect_029_explosion");
		Renderer->SetPivot({ 0, -100 });
		Renderer->SetDeleteEndFrame_(true);
	}

	{
		std::string TmpName = "explosions";
		TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(0, 2)) + ".wav";
		GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 0.01f * Option_SFX);
	}

	// 폭발자국 남기기
	PlayLevel* TmpLevel = dynamic_cast<PlayLevel*>(GetLevel());
	{
		GameEngineRenderer* Renderer = TmpLevel->GlobalActor->CreateRenderer("effect_017_bombradius.bmp", (int)ORDER::BACKGROUND);
		Renderer->SetIndex(GameEngineRandom::MainRandom->RandomInt(0, 7));
		Renderer->SetPivot(GetPosition());
		Renderer->SetAlpha(200);
	}

	// 주변에 대미지 주기
	GameEngineCollision* Collision = TmpLevel->GlobalActor->CreateCollision("BombEffect", { 288, 192 }, GetPosition());
	Collision->Death(0.1f);

	std::vector<GameEngineCollision*> ResultVector;
	if (true == Collision->CollisionResultRect("Stone", ResultVector))
	{
		for (int i = 0; i < ResultVector.size(); i++)
		{
			Stone* TmpActor = dynamic_cast<Stone*>(ResultVector[i]->GetActor());
			if (nullptr != TmpActor)
			{
				TmpActor->BombStone();
			}
		}
	}

	ResultVector.clear();
	if (true == Collision->CollisionResultRect("Monster", ResultVector))
	{
		for (int i = 0; i < ResultVector.size(); i++)
		{
			Monster* TmpActor = dynamic_cast<Monster*>(ResultVector[i]->GetActor());
			if (nullptr != TmpActor)
			{
				TmpActor->Damaged(60);
			}
		}
	}

	ResultVector.clear();
	if (true == Collision->CollisionResultRect("Player", ResultVector))
	{
		for (int i = 0; i < ResultVector.size(); i++)
		{
			Player* TmpActor = dynamic_cast<Player*>(ResultVector[i]->GetActor());
			if (nullptr != TmpActor)
			{
				TmpActor->GetPlayerUI()->GetPlayerHP()->MinusHearts(false);
			}
		}
	}

	ResultVector.clear();
	if (true == Collision->CollisionResultRect("Poop", ResultVector))
	{
		for (int i = 0; i < ResultVector.size(); i++)
		{
			Poop* TmpActor = dynamic_cast<Poop*>(ResultVector[i]->GetActor());
			if (nullptr != TmpActor)
			{
				TmpActor->AddHp(-60);
			}
		}
	}

	ResultVector.clear();
	if (true == Collision->CollisionResultRect("Fire", ResultVector))
	{
		for (int i = 0; i < ResultVector.size(); i++)
		{
			Fire* TmpActor = dynamic_cast<Fire*>(ResultVector[i]->GetActor());
			if (nullptr != TmpActor)
			{
				TmpActor->AddFireHP(-60);
			}
		}
	}

	ResultVector.clear();
	if (true == Collision->CollisionResultRect("Item", ResultVector))
	{
		for (int i = 0; i < ResultVector.size(); i++)
		{
			ItemBase* TmpActor = dynamic_cast<ItemBase*>(ResultVector[i]->GetActor());
			if (nullptr != TmpActor)
			{
				float4 TmpDir = TmpActor->GetPosition() - GetPosition();
				TmpDir.Normal2D();
				TmpActor->AddDir(TmpDir * 2.0f);
			}
		}
	}


	ResultVector.clear();
	if (true == Collision->CollisionResultRect("ShopKeeper", ResultVector))
	{
		for (int i = 0; i < ResultVector.size(); i++)
		{
			ShopKeeper* TmpActor = dynamic_cast<ShopKeeper*>(ResultVector[i]->GetActor());
			if (nullptr != TmpActor)
			{
				TmpActor->DeadAnim();
			}
		}
	}
}

