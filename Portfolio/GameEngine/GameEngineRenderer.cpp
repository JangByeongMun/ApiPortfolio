#include "GameEngineRenderer.h"
#include "GameEngine.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>

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
	GameEngineImage* findImage = GameEngineImageManager::GetInst()->Find(_name);
	if (nullptr == findImage)
	{
		MsgBoxAssertString(_name + " �������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	image_ = findImage;
	SetImageScale();
}


void GameEngineRenderer::SetImageScale()
{
	scaleMode_ = RenderScaleMode::Image;
	renderScale_ = image_->GetScale();
	renderImageScale_ = image_->GetScale();
}

void GameEngineRenderer::SetIndex(const size_t _index, float4 _scale)
{
	if (false == image_->IsCut())
	{
		MsgBoxAssert("�߷������� ���� �̹����Դϴ�.");
		return;
	}

	if (-1.0f == _scale.x || -1.0f == _scale.y)
	{
		renderScale_ = image_->GetCutScale(_index);
	}
	else
	{
		renderScale_ = _scale;
	}
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