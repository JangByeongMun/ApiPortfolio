#include "Credit05.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

Credit05::Credit05() 
{
}

Credit05::~Credit05() 
{
}

void Credit05::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	{
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -50, -40 });
		renderer->CreateAnimation("epilogue05_1.bmp", "epilogue05_1", 0, 1, 0.1f, true);
		renderer->ChangeAnimation("epilogue05_1");
	}
	
	{   // �Ȱ��� �� ����ϹǷ� 4_2 ��Ȱ��
		GameEngineRenderer* renderer = CreateRenderer(RenderPivot::CENTER, { -20, -100 });
		renderer->CreateAnimation("epilogue04_2.bmp", "epilogue04_2", 0, 1, 0.2f, true);
		renderer->ChangeAnimation("epilogue04_2");
	}
}

