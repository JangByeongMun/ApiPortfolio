#include "LoadingMap.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsGlobal.h"
#include "BindingOfIsaac.h"

LoadingMap::LoadingMap() 
	: PlayerRenderer_(nullptr)
	, AnimTimer_(0.0f)
{
}

LoadingMap::~LoadingMap() 
{
}

void LoadingMap::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half() + float4(0, -300));
	
	GameEngineRenderer* rendererLine1 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(-150, 0));
	rendererLine1->SetIndex(4);
	GameEngineRenderer* rendererLine2 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(-50, 0));
	rendererLine2->SetIndex(4);
	GameEngineRenderer* rendererLine3 = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(50, 0));
	rendererLine3->SetIndex(4);

	{
		GameEngineRenderer* Renderer = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(-100, 0));
		Renderer->SetIndex(8);
		FloorMaps_.push_back(Renderer);
	}

	{
		GameEngineRenderer* Renderer = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(0, 0));
		Renderer->SetIndex(1);
		FloorMaps_.push_back(Renderer);
	}

	{
		GameEngineRenderer* Renderer = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(100, 0));
		Renderer->SetIndex(1);
		FloorMaps_.push_back(Renderer);
	}
	
	PlayerRenderer_ = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(0, 0));
	PlayerRenderer_->SetIndex(5);

	GameEngineRenderer* rendererBoss = CreateRenderer("LoadingMap.bmp", RenderPivot::CENTER, float4(200, 20));
	rendererBoss->SetIndex(6);
}

void LoadingMap::Update()
{
	AnimTimer_ += GameEngineTime::GetDeltaTime();
	float4 LerpPos = float4::Lerp(FloorMaps_[CurrentFloor - 1]->GetPivot(), FloorMaps_[CurrentFloor]->GetPivot(), AnimTimer_);
	PlayerRenderer_->SetPivot(LerpPos);

	if (AnimTimer_ >= 2.5f)
	{
		BindingOfIsaac* TmpEngine = dynamic_cast<BindingOfIsaac*>(&GameEngine::GetInst());
		if (nullptr != TmpEngine)
		{
			TmpEngine->ResetPlayLevel("Play");
			TmpEngine->ChangeLevel("Play");
			CurrentFloor += 1;
		}
	}
}

void LoadingMap::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	AnimTimer_ = 0.0f;
	for (int i = 0; i < FloorMaps_.size(); i++)
	{
		if (i <= CurrentFloor)
		{
			if (i == 0)
			{
				FloorMaps_[i]->SetIndex(8);
			}
			if (i == 1)
			{
				FloorMaps_[i]->SetIndex(10);
			}
			if (i == 2)
			{
				FloorMaps_[i]->SetIndex(12);
			}

			continue;
		}

		FloorMaps_[i]->SetIndex(1);
	}
}