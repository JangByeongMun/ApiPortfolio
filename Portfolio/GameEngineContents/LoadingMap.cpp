#include "LoadingMap.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsGlobal.h"

LoadingMap::LoadingMap() 
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

void LoadingMap::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayerRenderer_->SetPivot(FloorMaps_[CurrentFloor - 1]->GetPivot());
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

