#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine.h"

GameEngineActor::GameEngineActor() 
	: level_(nullptr)
	, position_()
	, scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
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
