#include "BoomEffect.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "PlayLevel.h"
#include "Stone.h"
#include "Monster.h"
#include "Player.h"
#include "PlayerUI.h"
#include "PlayerHP.h"	
#include "Poop.h"
#include "Fire.h"
#include "ContentsEnum.h"
#include "ContentsGlobal.h"
#include "ShopKeeper.h"
#include "ItemBase.h"

BoomEffect::BoomEffect() 
{
}

BoomEffect::~BoomEffect() 
{
}

void BoomEffect::Setting(float4 _Pos)
{
	SetPosition(_Pos);
	MakeEffect();
}

void BoomEffect::MakeEffect()
{
	// 폭발 이펙트 생성
	{
		GameEngineRenderer* Renderer = CreateRenderer("effect_029_explosion2.bmp", static_cast<int>(ORDER::UI));
		Renderer->SetAlpha(100);
		Renderer->SetPivot({ 0, -100 });
		Renderer->Death(0.35f);
	}

	{
		GameEngineRenderer* Renderer = CreateRenderer("effect_029_explosion.bmp", static_cast<int>(ORDER::UI));
		Renderer->CreateAnimation("effect_029_explosion.bmp", "Explosion", 0, 11, 0.05f, false);
		Renderer->ChangeAnimation("Explosion");
		Renderer->SetPivot({ 0, -100 });
		Renderer->SetDeleteEndFrame_(true);
	}

	{
		std::string TmpName = "explosions";
		TmpName += std::to_string(GameEngineRandom::MainRandom->RandomInt(0, 2)) + ".wav";
		GameEngineSound::SoundPlayOneShotWithVolume(TmpName, 0, 1.0f * Option_SFX);
	}

	{
		// 폭발자국 남기기
		PlayLevel* TmpLevel = dynamic_cast<PlayLevel*>(GetLevel());
		if (TmpLevel == nullptr)
		{
			return;
		}

		GameEngineRenderer* Renderer = TmpLevel->GlobalActor->CreateRenderer("effect_017_bombradius.bmp", (int)ORDER::BACKGROUND);
		Renderer->SetIndex(GameEngineRandom::MainRandom->RandomInt(0, 7));
		Renderer->SetPivot(GetPosition());
		Renderer->SetAlpha(200);

		// 주변에 대미지 주기
		GameEngineCollision* Collision = TmpLevel->GlobalActor->CreateCollision("BombEffect", { 288, 192 }, GetPosition());

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

		Collision->Death(0.1f);
	}
}

