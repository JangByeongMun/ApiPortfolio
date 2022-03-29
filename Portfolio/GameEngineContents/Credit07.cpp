#include "Credit07.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit07::Credit07() 
{
}

Credit07::~Credit07() 
{
}

void Credit07::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("epilogue07_1.bmp", RenderPivot::CENTER, {-20, -20});

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, {20, 100});
	renderer->CreateAnimation("epilogue07_2.bmp", "epilogue07_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue07_2");
}

