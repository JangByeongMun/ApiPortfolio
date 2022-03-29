#include "Credit02.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit02::Credit02() 
{
}

Credit02::~Credit02() 
{
}

void Credit02::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, {-5, 0});
	renderer->CreateAnimation("epilogue02_1.bmp", "epilogue02_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue02_1");
}

