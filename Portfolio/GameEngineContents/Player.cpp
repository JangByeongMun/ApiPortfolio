#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Projectile.h"

Player::Player() 
	: speed_(100.0f)
	, bodyRender_()
	, headRender_()
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	bodyRender_ = CreateRenderer("character_001_isaac.bmp", RenderPivot::CENTER, { 0, 35 });
	bodyRender_->SetIndex(8);
	
	headRender_ = CreateRenderer("character_001_isaac.bmp", RenderPivot::CENTER, { 0, 0 });
	headRender_->SetIndex(0);


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
		GameEngineInput::GetInst()->CreateKey("Bomb", VK_SPACE);
	}
}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::Left * GameEngineTime::GetInst()->GetDeltaTime() * speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::Right * GameEngineTime::GetInst()->GetDeltaTime() * speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::Up * GameEngineTime::GetInst()->GetDeltaTime() * speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::Down * GameEngineTime::GetInst()->GetDeltaTime() * speed_);
	}

	if (true == GameEngineInput::GetInst()->IsDown("AttckLeft"))
	{
		Projectile* ptr = GetLevel()->CreateActor<Projectile>();
		ptr->SetPosition(GetPosition());
		ptr->SetVector(float4::Left);
		ptr->SetSpeed(200.0f);
	}
	if (true == GameEngineInput::GetInst()->IsDown("AttckRight"))
	{
		Projectile* ptr = GetLevel()->CreateActor<Projectile>();
		ptr->SetPosition(GetPosition());
		ptr->SetVector(float4::Right);
		ptr->SetSpeed(200.0f);
	}
	if (true == GameEngineInput::GetInst()->IsDown("AttckUp"))
	{
		Projectile* ptr = GetLevel()->CreateActor<Projectile>();
		ptr->SetPosition(GetPosition());
		ptr->SetVector(float4::Up);
		ptr->SetSpeed(200.0f);
	}
	if (true == GameEngineInput::GetInst()->IsDown("AttckDown"))
	{
		Projectile* ptr = GetLevel()->CreateActor<Projectile>();
		ptr->SetPosition(GetPosition());
		ptr->SetVector(float4::Down);
		ptr->SetSpeed(200.0f);
	}
}

void Player::Render()
{
	
}
