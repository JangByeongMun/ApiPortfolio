#include "Projectile.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "PlayLevel.h"

Projectile::Projectile() 
	: Collision_()
	, Type_(ProjectileType::PLAYER_BASIC)
	, Vec_({ 0, 0 })
	, Lifetime_(0)
	, CurrentTimer_(0)
{
}

Projectile::~Projectile() 
{
}

void Projectile::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("tears.bmp", RenderPivot::CENTER, { 0, 0 });
	Renderer->SetIndex(5);
	
	Collision_ = CreateCollision("Projectile", { 30, 30 }, { 0, 0 });
}

void Projectile::Update()
{
	CurrentTimer_ += GameEngineTime::GetDeltaTime();

	if (Lifetime_ - CurrentTimer_ <= 0.3f)
	{
		Vec_ += {0, 600 * GameEngineTime::GetDeltaTime()};
	}

	// 설정한 시간이 지나면 삭제
	if (Lifetime_ - CurrentTimer_ <= 0.0f)
	{
		DestroyTear();
	}

	// 벽을 못넘어가도록 넘어가려고하면 삭제
	int Color = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp")->GetImagePixel(GetPosition());
	if (RGB(0, 0, 0) == Color)
	{
		DestroyTear();
	}

	SetMove(Vec_ * GameEngineTime::GetDeltaTime());
}

void Projectile::DestroyTear()
{
	PlayLevel* TmpLevel = static_cast<PlayLevel*>(GetLevel());
	GameEngineRenderer* TmpRenderer = TmpLevel->GlobalActor->CreateRenderer("effect_015_tearpoofa.bmp");
	TmpRenderer->CreateAnimation("effect_015_tearpoofa.bmp", "effect_015_tearpoofa", 0, 15, 0.02f, false);
	TmpRenderer->ChangeAnimation("effect_015_tearpoofa");
	TmpRenderer->SetDeleteEndFrame_(true);
	TmpRenderer->SetPivot(GetPosition());
	Death();
}

