#include "GameEngineRenderer.h"
#include "GameEngine.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineRenderer::GameEngineRenderer() 
	: image_{}
	, pivotType_{}
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImage(const std::string& _name)
{
	GameEngineImage* findImage = GameEngineImageManager::GetInst()->Find("Player.bmp");
	if (nullptr == findImage)
	{
		MsgBoxAssertString(_name + " �������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	image_ = findImage;
}

void GameEngineRenderer::Render()
{
	GameEngine::BackBufferImage()->BitCopyCenter(image_, GetPosition());
}

float4 GameEngineRenderer::GetPosition()
{
	return float4();
}

