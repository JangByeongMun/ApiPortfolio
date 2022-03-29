#include "Credit04.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit04::Credit04() 
{
}

Credit04::~Credit04() 
{
}

void Credit04::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 0, 20 });
		renderer->CreateAnimation("epilogue04_1.bmp", "epilogue04_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue04_1");
	}

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 10, 80 });
		renderer->CreateAnimation("epilogue04_2.bmp", "epilogue04_2", 0, 1, 0.2f, true);
		renderer->ChangeAnimation("epilogue04_2");
	}
}

