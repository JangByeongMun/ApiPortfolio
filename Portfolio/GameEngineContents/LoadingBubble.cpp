#include "LoadingBubble.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

LoadingBubble::LoadingBubble() 
	: AnimTimer_(0.0f)
{
}

LoadingBubble::~LoadingBubble() 
{
}

void LoadingBubble::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half() + float4{ 0, 190 });

	RendererVector.push_back(CreateRenderer("LoadingBubble3.bmp", RenderPivot::CENTER, { 0, -250 }));
	RendererVector.push_back(CreateRenderer("LoadingBubble2.bmp", RenderPivot::CENTER, { -130, -80 }));
	RendererVector.push_back(CreateRenderer("LoadingBubble1.bmp", RenderPivot::CENTER, { -60, -45 }));
}

void LoadingBubble::Update()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();

	if (AnimTimer_ >= 0.2f)
	{
		RendererVector[2]->On();
	}
	
	if (AnimTimer_ >= 0.4f)
	{
		RendererVector[1]->On();
	}

	if (AnimTimer_ >= 0.6f)
	{
		RendererVector[0]->On();
	}
}

void LoadingBubble::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	AnimTimer_ = 0.0f;
	for (int i = 0; i < RendererVector.size(); i++)
	{
		RendererVector[i]->Off();
	}
}

