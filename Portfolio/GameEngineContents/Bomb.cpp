#include "Bomb.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "PlayLevel.h"
#include "Projectile.h"
#include "Stone.h"
#include "Monster.h"
#include "Player.h"
#include "PlayerUI.h"
#include "PlayerHP.h"

Bomb::Bomb() 
	: Collision_(nullptr)
	, Renderer_(nullptr)
	, Timer_ (0.0f)
	, BombTime_(2.0f)
	, IsExplode(false)
{
}

Bomb::~Bomb() 
{
}

void Bomb::Start()
{
	Collision_ = CreateCollision("Bomb", { 80, 80 }, { 0, 0 });
	Renderer_ = CreateRenderer(RenderPivot::CENTER, GetPosition());
	Renderer_->CreateAnimation("pickup_016_bomb_One.bmp", "pickup_016_bomb_One", 0, 2, 0.2f, true);
	Renderer_->ChangeAnimation("pickup_016_bomb_One");
}

void Bomb::Update()
{
	if (true == IsExplode)
	{
		return;
	}

	Timer_ += GameEngineTime::GetDeltaTime();
	BompAnimation();
	
	std::vector<GameEngineCollision*> CollisionResult_;
	if (true == Collision_->CollisionResult("Projectile", CollisionResult_, CollisionType::Rect, CollisionType::Rect))
	{
		float4 MoveDir = { 0, 0 };
		for (int i = 0; i < CollisionResult_.size(); i++)
		{
			if (CollisionResult_[i] == nullptr)
			{
				continue;
			}

			Projectile* TmpProjectile = static_cast<Projectile*>(CollisionResult_[i]->GetActor());
			TmpProjectile->DestroyProjectile();

			MoveDir += (GetPosition() - CollisionResult_[i]->GetCollisionPos()) * 10.0f;
		}

		SetMove(MoveDir * 0.1f);
	}
	CollisionResult_.clear();

	if (Timer_ >= BombTime_)
	{
		IsExplode = true;
		// 폭발 이펙트 생성
		{
			GameEngineRenderer* Renderer = CreateRenderer("effect_029_explosion2.bmp", static_cast<int>(ORDER::UI));
			Renderer->SetAlpha(100);
			Renderer->SetPivot({0, -100});
			Renderer->Death(0.35f);
		}

		{
			GameEngineRenderer* Renderer = CreateRenderer(static_cast<int>(ORDER::UI), RenderPivot::CENTER);
			Renderer->CreateAnimation("effect_029_explosion.bmp", "effect_029_explosion", 0, 11, 0.05f, false);
			Renderer->ChangeAnimation("effect_029_explosion");
			Renderer->SetPivot({ 0, -100 });
			Renderer->SetDeleteEndFrame_(true);
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
		GameEngineCollision* Collision = TmpLevel->GlobalActor->CreateCollision("BombEffect", {288, 192}, GetPosition());
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
					TmpActor->GetPlayerUI()->GetPlayerHP()->AddRedHp(-1, false);
				}
			}
		}

		Renderer_->Death();
		Collision_->Death();
		Death(1.0f);
	}
}

void Bomb::BompAnimation()
{
	if (Timer_ <= 0.25f)
	{
		Renderer_->SetScale({ 86, 106 });
	}
	else if (Timer_ <= 0.5f)
	{
		Renderer_->SetScale({ 106, 86 });
	}
	else if (Timer_ <= 0.75f)
	{
		Renderer_->SetScale({ 86, 106 });
	}
	else if (Timer_ <= 1.0f)
	{
		Renderer_->SetScale({ 106, 86 });
	}

	else if (Timer_ <= 1.125f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 1.25f)
	{
		Renderer_->SetScale({ 126, 66 });
	}
	else if (Timer_ <= 1.375f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 1.5f)
	{
		Renderer_->SetScale({ 126, 66 });
	}

	else if (Timer_ <= 1.625f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 1.75f)
	{
		Renderer_->SetScale({ 126, 66 });
	}
	else if (Timer_ <= 1.875f)
	{
		Renderer_->SetScale({ 66, 126 });
	}
	else if (Timer_ <= 2.0f)
	{
		Renderer_->SetScale({ 126, 66 });
	}
}
