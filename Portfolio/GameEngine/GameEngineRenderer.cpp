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
		MsgBoxAssertString(_name + " 존재하지 않는 이미지를 렌더러에 세팅하려고 했습니다.");
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

