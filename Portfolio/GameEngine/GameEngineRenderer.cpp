#include "GameEngineRenderer.h"
#include "GameEngine.h"
#include "GameEngineImage.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

#pragma comment(lib, "msimg32.lib")

RenderScaleMode scaleMode_;
float4 renderPivot_;
float4 renderScale_;
unsigned int TransColor_;

GameEngineRenderer::GameEngineRenderer() 
	: image_(nullptr)
	, pivotType_(RenderPivot::CENTER)
	, scaleMode_(RenderScaleMode::Image)
	, renderPivot_{0, 0}
	, renderScale_{0, 0}
	, TransColor_(RGB(255, 0, 255))
	, renderImagePivot_{0, 0}
	, renderImageScale_{0, 0}
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
		MsgBoxAssertString(_name + " �������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	image_ = findImage;
}


void GameEngineRenderer::SetImageScale()
{
	scaleMode_ = RenderScaleMode::Image;
	renderScale_ = image_->GetScale();
	renderImageScale_ = image_->GetScale();
}

void GameEngineRenderer::SetIndex(const size_t _index)
{
	if (false == image_->IsCut())
	{
		MsgBoxAssert("�߷������� ���� �̹����Դϴ�.");
		return;
	}

	renderScale_ = image_->GetCutScale(_index);
	renderImagePivot_ = image_->GetCutPivot(_index);
	renderImageScale_ = image_->GetCutScale(_index);
}

void GameEngineRenderer::Render()
{
	if (nullptr == image_)
	{
		MsgBoxAssert("�������� �̹����� �������� �ʾҽ��ϴ�.");
		return;
	}

	float4 renderPos = GetActor()->GetPosition() + renderPivot_;

	switch (pivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(image_, renderPos - renderScale_.Half(), renderScale_, renderImagePivot_, renderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
		// ���� �������� �� ���� ��а� ������ �켱 ���� �ٸ��ͺ��� �۾�
		//GameEngine::BackBufferImage()->TransCopy(image_, renderPos - renderScale_.Half(), renderScale_, renderImagePivot_, renderImageScale_, TransColor_);
		break;
	default:
		break;
	}
}