#include "GameEngineActor.h"
#include "GameEngine.h"
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"

#include <GameEngineBase/GameEngineWindow.h>

GameEngineActor::GameEngineActor() 
	: Level_(nullptr)
	, Position_()
	, Scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
	// 렌더리스트 삭제
	{
		std::list<GameEngineRenderer*>::iterator BeginIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();
		for (; BeginIter != EndIter; ++BeginIter)
		{
			if (nullptr == (*BeginIter))
			{
				continue;
			}
			delete (*BeginIter);
			(*BeginIter) = nullptr;
		}
	}

	// 충돌 삭제
	{
		std::list<GameEngineCollision*>::iterator BeginIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();
		for (; BeginIter != EndIter; ++BeginIter)
		{
			if (nullptr == (*BeginIter))
			{
				continue;
			}
			delete (*BeginIter);
			(*BeginIter) = nullptr;
		}
	}
}

void GameEngineActor::Start()
{
}

void GameEngineActor::Update()
{
}

void GameEngineActor::Render()
{
}

void GameEngineActor::Release()
{
	// 렌더가 종료된게 있으면 확인후 삭제
	{
		std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

		for (; StartIter != EndIter;)
		{
			if (false == (*StartIter)->IsDeath())
			{
				++StartIter;
				continue;
			}

			delete (*StartIter);
			StartIter = RenderList_.erase(StartIter);
		}
	}

	// 충돌이 종료된게 있으면 확인후 삭제
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList_.end();

		for (; StartIter != EndIter;)
		{
			if (false == (*StartIter)->IsDeath())
			{
				++StartIter;
				continue;
			}

			delete (*StartIter);
			StartIter = CollisionList_.erase(StartIter);
		}
	}
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);
	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetPivotType(_PivotType);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Image, RenderPivot _PivotType, float4 _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRendererToScale(const std::string& _Image, float4 _Scale, RenderPivot _PivotType, float4 _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetScale(_Scale);
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

void GameEngineActor::Rendering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();
	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		if (false == (*StartRenderIter)->IsUpdate())
		{
			continue;
		}

		(*StartRenderIter)->Render();
	}
}

GameEngineCollision* GameEngineActor::CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();
	NewCollision->SetActor(this);
	NewCollision->SetPivot(_Pivot);
	NewCollision->SetScale(_Scale);

	GetLevel()->AddCollision(_GroupName, NewCollision);
	CollisionList_.push_back(NewCollision);
	return NewCollision;
}
