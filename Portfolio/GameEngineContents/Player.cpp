#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>

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
}

void Player::Update()
{
}

void Player::Render()
{
	//GameEngineImage* findImage = GameEngineImageManager::GetInst()->Find("Player.bmp");
	//if (nullptr == findImage)
	//{
	//	MsgBoxAssert("플레이어 이미지를 찾지 못했습니다.");
	//	return;	
	//}
	//GameEngine::BackBufferImage()->BitCopyCenter(findImage, GetPosition());

	//CreateRenderer("Player.bmp", RenderPivot::CENTER, { 0, 0 });
}
