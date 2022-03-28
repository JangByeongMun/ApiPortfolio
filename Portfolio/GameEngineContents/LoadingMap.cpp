#include "LoadingMap.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


LoadingMap::LoadingMap() 
{
}

LoadingMap::~LoadingMap() 
{
}

void LoadingMap::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half() + float4(0, -300));
	
	GameEngineRenderer* rendererPlayer = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(200, 20));
	rendererPlayer->SetIndex(5);

	GameEngineRenderer* rendererLine1 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(-150, 0));
	rendererLine1->SetIndex(4);
	GameEngineRenderer* rendererLine2 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(-50, 0));
	rendererLine2->SetIndex(4);
	GameEngineRenderer* rendererLine3 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(50, 0));
	rendererLine3->SetIndex(4);
	GameEngineRenderer* rendererLine4 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(150, 0));
	rendererLine4->SetIndex(4);

	GameEngineRenderer* renderer1 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(-200, 0));
	renderer1->SetIndex(8);
	GameEngineRenderer* renderer2 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(-100, 0));
	renderer2->SetIndex(1);
	GameEngineRenderer* renderer3 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(0, 0));
	renderer3->SetIndex(1);
	GameEngineRenderer* renderer4 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(100, 0));
	renderer4->SetIndex(1);
	GameEngineRenderer* renderer5 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(200, 0));
	renderer5->SetIndex(1);

	GameEngineRenderer* rendererBoss = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(200, 20));
	rendererBoss->SetIndex(6);
}

