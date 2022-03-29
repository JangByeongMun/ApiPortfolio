#include "GameEngineRenderer.h"
#include "GameEngine.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>


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
	if (nullptr != currentAnimation_)
	{
		currentAnimation_->Update();
	}

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

//////////////////////////// �ִϸ��̼�


void GameEngineRenderer::CreateAnimation(
	const std::string& _image,
	const std::string& _name,
	int _startIndex,
	int _endIndex,
	float _interTime,
	bool _loop
)
{
	GameEngineImage* findImage = GameEngineImageManager::GetInst()->Find(_image);
	if (nullptr == findImage)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	std::map<std::string, FrameAnimation>::iterator findIter = animations_.find(_name);
	if (animations_.end() != findIter)
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼ǿ� �߰��Ϸ��� �߽��ϴ�.");
		return;
	}

	FrameAnimation& newAnimation = animations_[_name];
	newAnimation.renderer_ = this;
	newAnimation.image_ = findImage;
	newAnimation.currentFrame_ = _startIndex;
	newAnimation.startFrame_ = _startIndex;
	newAnimation.endFrame_ = _endIndex;
	newAnimation.currentInterTime_ = _interTime;
	newAnimation.interTime_ = _interTime;
	newAnimation.loop_ = _loop;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _name)
{
	std::map<std::string, FrameAnimation>::iterator findIter = animations_.find(_name);
	if (animations_.end() == findIter)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� �����Ϸ� �߽��ϴ�.");
		return;
	}

	currentAnimation_ = &findIter->second;
}

void GameEngineRenderer::FrameAnimation::Update()
{
	currentInterTime_ -= GameEngineTime::GetInst()->GetDeltaTime();
	if (0 >= currentInterTime_)
	{
		currentInterTime_ = interTime_;
		++currentFrame_;

		if (endFrame_ < currentFrame_)
		{
			if (true == loop_)
			{
				currentFrame_ = startFrame_;
			}
			else
			{
				currentFrame_ = endFrame_;
			}
		}
	}

	renderer_->image_ = image_;
	renderer_->SetIndex(currentFrame_);
}
