#include "Bomb.h"
#include <GameEngineBase/GameEngineTime.h>

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
	Collision_ = CreateCollision("Bomb", { 96, 96 }, { 0, 0 });
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

			MoveDir += GetPosition() - CollisionResult_[i]->GetCollisionPos();
		}

		SetMove(MoveDir * 0.1f);
	}

	if (Timer_ >= BombTime_)
	{
		// 폭발자국 남기기
		//CreateRenderer();

		// 주변에 대미지 주기
		//

		Death();
	}
}