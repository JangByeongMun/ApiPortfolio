#include "Credit09.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit09::Credit09() 
{
}

Credit09::~Credit09() 
{
}

void Credit09::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("epilogue09_1.bmp", RenderPivot::CENTER, {-50, 10});

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, {20, 65});
	renderer->CreateAnimation("epilogue09_2.bmp", "epilogue09_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue09_2");
}

