#include "LoadingCharacter.h"
#include <GameEngineBase/GameEngineWindow.h>

LoadingCharacter::LoadingCharacter() 
{
}

LoadingCharacter::~LoadingCharacter() 
{
}

void LoadingCharacter::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("LoadingCharacter1.bmp");
}

