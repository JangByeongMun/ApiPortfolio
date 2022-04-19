#include "Bomb.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "PlayLevel.h"
#include "Projectile.h"

Bomb::Bomb() 
	: Timer_ (0)
	, BombTime_(3)
{
}

Bomb::~Bomb() 
{
}

void Bomb::Start()
{
	CreateRenderer("collectibles_045_yumheart.bmp", RenderPivot::CENTER, GetPosition());
	Collision_ = CreateCollision("Bomb", { 80, 80 }, { 0, 0 });
}

void Bomb::Update()
{
	Timer_ += GameEngineTime::GetDeltaTime();

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
			TmpProjectile->DestroyTear();

			MoveDir += (GetPosition() - CollisionResult_[i]->GetCollisionPos()) * 10.0f;
		}

		SetMove(MoveDir * 0.1f);
	}
	CollisionResult_.clear();

	if (Timer_ >= BombTime_)
	{
		// 폭발자국 남기기
		PlayLevel* TmpLevel = static_cast<PlayLevel*>(GetLevel());
		GameEngineRenderer* Renderer = TmpLevel->GlobalActor->CreateRenderer("effect_017_bombradius.bmp", (int)ORDER::BACKGROUND);
		Renderer->SetIndex(GameEngineRandom::MainRandom->RandomInt(0, 7));
		Renderer->SetPivot(GetPosition());
		Renderer->SetAlpha(150);

		// 주변에 대미지 주기


		Death();
	}
}