#include "LoadingBubble.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include "LoadingAnim1.h"
#include "LoadingAnim2.h"

LoadingBubble::LoadingBubble() 
	: AnimTimer_(0.0f)
	, CreateNightmare(false)
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

	if (AnimTimer_ >= 0.8f && CreateNightmare == false)
	{
		//GetLevel()->CreateActor<LoadingAnim1>()->SetPosition(GetPosition() + float4(0, -250));
		GetLevel()->CreateActor<LoadingAnim2>()->SetPosition(GetPosition() + float4(0, -250));
		CreateNightmare = true;
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

