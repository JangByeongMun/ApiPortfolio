#include "Credit01.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit01::Credit01() 
{
}

Credit01::~Credit01() 
{
}

void Credit01::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("epilogue01_1.bmp", RenderPivot::CENTER, {-20, -20});

	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, {5, 15});
	renderer->CreateAnimation("epilogue01_2.bmp", "epilogue01_2", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue01_2");
}

