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
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4{0, 150});

	CreateRenderer("LoadingCharacter1.bmp");
	CreateRenderer("LoadingBubble.bmp", RenderPivot::CENTER, {0, -200});
}

