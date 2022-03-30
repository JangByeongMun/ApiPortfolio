#include "Credit14.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit14::Credit14() 
{
}

Credit14::~Credit14() 
{
}

void Credit14::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, {-30, 135});
	renderer->CreateAnimation("epilogue14_1.bmp", "epilogue14_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue14_1");
}

