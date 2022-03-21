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
}

void Player::Update()
{
}

void Player::Render()
{
	//Rectangle(GameEngineWindow::GetHDC(), 500, 500, 550, 550);
	
	//GameEngineImage* findImage = GameEngineImageManager::GetInst()->Find("Player.bmp");
	//if (nullptr == findImage)
	//{
	//	MsgBoxAssert("�÷��̾� �̹����� ã�� ���߽��ϴ�.");
	//	return;	
	//}
	//GameEngine::BackBufferImage()->BitCopyCenter(findImage, GetPosition());

	CreateRenderer("Player.bmp", RenderPivot::CENTER, { 0, 0 });
}
