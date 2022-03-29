#include "Credit06.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit06::Credit06() 
{
}

Credit06::~Credit06() 
{
}

void Credit06::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	CreateRenderer("epilogue06_1.bmp", RenderPivot::CENTER, { 35, -50 });

	// �Ȱ��� �� ����ϹǷ� 5_1 ��Ȱ��
	GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { 5, 15 });
	renderer->CreateAnimation("epilogue05_1.bmp", "epilogue05_1", 0, 1, 0.1f, true);
	renderer->ChangeAnimation("epilogue05_1");
}

