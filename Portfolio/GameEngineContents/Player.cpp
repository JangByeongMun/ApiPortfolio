#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });
	
	CreateRenderer("Player.bmp", RenderPivot::CENTER, { 0, 0 });
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
		SetMove(float4::Left/* * GameEngineTime::GetInst()->GetDeltaTime()*/);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::Right);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::Up);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::Down);
	}

	if (true == GameEngineInput::GetInst()->IsPress("AttckLeft"))
	{
		SetMove(float4::Left/* * GameEngineTime::GetInst()->GetDeltaTime()*/);
	}
	if (true == GameEngineInput::GetInst()->IsPress("AttckRight"))
	{
		SetMove(float4::Right);
	}
	if (true == GameEngineInput::GetInst()->IsPress("AttckUp"))
	{
		SetMove(float4::Up);
	}
	if (true == GameEngineInput::GetInst()->IsPress("AttckDown"))
	{
		SetMove(float4::Down);
	}
}

void Player::Render()
{
	
}
