#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineActor::GameEngineActor() 
	: level_(nullptr)
	, position_()
	, scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(position_, scale_);
	Rectangle(
		GameEngineWindow::GetHDC(),
		DebugRect.GetCenterLeft(),
		DebugRect.GetCenterTop(),
		DebugRect.GetCenterRight(),
		DebugRect.GetCenterBot()
	);
}
