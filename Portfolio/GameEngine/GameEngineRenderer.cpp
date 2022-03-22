#include "GameEngineRenderer.h"
#include "GameEngine.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer() 
	: image_(nullptr)
	, pivotType_(RenderPivot::CENTER)
	, renderPivot_{0, 0}
	, TransColor_(RGB(255, 0, 255))
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImage(const std::string& _name)
{
	std::string engineName = GameEngineString::ToUpperReturn(_name);
	GameEngineImage* findImage = GameEngineImageManager::GetInst()->Find(engineName);
	if (nullptr == findImage)
	{
		MsgBoxAssertString(_name + " 존재하지 않는 이미지를 렌더러에 세팅하려고 했습니다.");
		return;
	}

	image_ = findImage;
}

void GameEngineRenderer::Render()
{
	if (nullptr == image_)
	{
		MsgBoxAssert("렌더러에 이미지를 세팅하지 않았습니다.");
		return;
	}

	float4 renderPos = GetActor()->GetPosition() + renderPivot_;
	float4 renderScale = renderScale_;

	switch (pivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopyCenterScale(image_, renderPos, renderScale, TransColor_);
		break;
	case RenderPivot::BOT:
		//GameEngine::BackBufferImage()->BitCopyBotPivot(image_, GetActor()->GetPosition(), renderPivot_);
		break;
	default:
		break;
	}
}