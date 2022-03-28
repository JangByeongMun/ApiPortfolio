#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include "GameEngineRenderer.h"

GameEngineActor::GameEngineActor() 
	: level_(nullptr)
	, position_()
	, scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
	std::list<GameEngineRenderer*>::iterator beginIter = renderList_.begin();
	std::list<GameEngineRenderer*>::iterator endIter = renderList_.end();
	for (; beginIter != endIter; ++beginIter)
	{
		if (nullptr == (*beginIter))
		{
			continue;
		}
		delete (*beginIter);
		(*beginIter) = nullptr;
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

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(position_, scale_);
	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.GetCenterLeft(),
		DebugRect.GetCenterTop(),
		DebugRect.GetCenterRight(),
		DebugRect.GetCenterBot()
	);
}

GameEngineRenderer* GameEngineActor::CreateRenderer(RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);

	renderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _image, RenderPivot _pivotType, float4 _pivotPos)
{
	GameEngineRenderer* newRenderer = new GameEngineRenderer();

	newRenderer->SetActor(this);
	newRenderer->SetImage(_image);
	newRenderer->SetType(_pivotType);
	newRenderer->SetPivot(_pivotPos);

	renderList_.push_back(newRenderer);
	return newRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRendererToScale(const std::string& _image, float4 _scale, RenderPivot _pivotType, float4 _pivotPos)
{
	GameEngineRenderer* newRenderer = new GameEngineRenderer();

	newRenderer->SetActor(this);
	newRenderer->SetImage(_image);
	newRenderer->SetScale(_scale);
	newRenderer->SetType(_pivotType);
	newRenderer->SetPivot(_pivotPos);

	renderList_.push_back(newRenderer);
	return newRenderer;
}

void GameEngineActor::Rendering()
{
	startRenderIter = renderList_.begin();
	endRenderIter = renderList_.end();
	for (; startRenderIter != endRenderIter; ++startRenderIter)
	{
		(*startRenderIter)->Render();
	}
}
