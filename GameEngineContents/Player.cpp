#include "Player.h"
#include <Windows.h>
#include "GameEngineBase/GameEngineWindow.h"

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
}

void Player::Update()
{
}

void Player::Render()
{
	Rectangle(GameEngineWindow::GETDC(), 500, 500, 550, 550);
}
