#include "Player.h"
#include <Windows.h>

#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>

#include "Projectile.h"

Player::Player() 
	: Speed_(300.0f)
	, BodyRender_(nullptr)
	, HeadRender_(nullptr)
	, MapColImage_(nullptr)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	MapColImage_ = GameEngineImageManager::GetInst()->Find("basementTestCol.bmp");

	BodyRender_ = CreateRenderer("character_001_isaac.bmp", RenderPivot::CENTER, { 0, 35 });
	BodyRender_->SetIndex(8);
	
	//HeadRender_ = CreateRenderer("character_001_isaac.bmp", RenderPivot::CENTER, { 0, 0 });
	//HeadRender_->SetIndex(0);


	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("AttckLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("AttckRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("AttckUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("AttckDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Bomb", 'E');
	}
}

void Player::Update()
{
	{
		float4 MoveDir = float4::ZERO;
		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			MoveDir = float4::LEFT;
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			MoveDir = float4::RIGHT;
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			MoveDir = float4::UP;
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			MoveDir = float4::DOWN;
		}

		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos;

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("AttckLeft"))
	{
		Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetVector(float4::LEFT);
		Ptr->SetSpeed(200.0f);
	}
	if (true == GameEngineInput::GetInst()->IsDown("AttckRight"))
	{
		Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetVector(float4::RIGHT);
		Ptr->SetSpeed(200.0f);
	}
	if (true == GameEngineInput::GetInst()->IsDown("AttckUp"))
	{
		Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetVector(float4::UP);
		Ptr->SetSpeed(200.0f);
	}
	if (true == GameEngineInput::GetInst()->IsDown("AttckDown"))
	{
		Projectile* Ptr = GetLevel()->CreateActor<Projectile>();
		Ptr->SetPosition(GetPosition());
		Ptr->SetVector(float4::DOWN);
		Ptr->SetSpeed(200.0f);
	}
}

void Player::Render()
{
}
