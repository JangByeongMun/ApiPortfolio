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
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4{0, 190});

	CreateRenderer("Loading_01_isaac.bmp");
	CreateRenderer("LoadingBubble3.bmp", RenderPivot::CENTER, { 0, -250 });
	CreateRenderer("LoadingBubble2.bmp", RenderPivot::CENTER, { -130, -80 });
	CreateRenderer("LoadingBubble1.bmp", RenderPivot::CENTER, { -60, -45 });
	//CreateRenderer("nightmare_9_1.bmp", RenderPivot::CENTER, { -50, -240 });
	//CreateRenderer("nightmare_9_1.bmp", RenderPivot::CENTER, { 0, -240 });
}

