#include "Credit03.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit03::Credit03() 
{
}

Credit03::~Credit03() 
{
}

void Credit03::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("epilogue03_1.bmp", RenderPivot::CENTER, {0, -10});

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, {10, 15});
	renderer->CreateAnimation("epilogue03_2.bmp", "epilogue03_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue03_2");
}

