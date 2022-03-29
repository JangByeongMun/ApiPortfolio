#include "Credit10.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit10::Credit10() 
{
}

Credit10::~Credit10() 
{
}

void Credit10::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, -150 });
		renderer->CreateAnimation("epilogue10_1.bmp", "epilogue10_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue10_1");
	}

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -30, 240 });
		renderer->CreateAnimation("epilogue10_2.bmp", "epilogue10_2", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue10_2");
	}
}

