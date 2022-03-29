#include "Credit08.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit08::Credit08() 
{
}

Credit08::~Credit08() 
{
}

void Credit08::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("epilogue08_1.bmp", RenderPivot::CENTER, {-40, 20});

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, {-30, 145});
	renderer->CreateAnimation("epilogue08_2.bmp", "epilogue08_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue08_2");
}

