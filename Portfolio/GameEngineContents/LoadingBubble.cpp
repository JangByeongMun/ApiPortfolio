#include "LoadingBubble.h"
#include <GameEngineBase/GameEngineWindow.h>

LoadingBubble::LoadingBubble() 
{
}

LoadingBubble::~LoadingBubble() 
{
}

void LoadingBubble::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4{ 0, 190 });

	CreateRenderer("LoadingBubble3.bmp", RenderPivot::CENTER, { 0, -250 });
	CreateRenderer("LoadingBubble2.bmp", RenderPivot::CENTER, { -130, -80 });
	CreateRenderer("LoadingBubble1.bmp", RenderPivot::CENTER, { -60, -45 });
}

