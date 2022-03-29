#pragma once
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// 설명 :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend class FrameAnimation;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;
	
	inline void SetType(const RenderPivot& _type)
	{
		pivotType_ = _type;
	}
	inline void SetScaleMode(const RenderScaleMode& _mode)
	{
		scaleMode_ = _mode;
	}
	inline void SetPivot(const float4& _pivot)
	{
		renderPivot_ = _pivot;
	}
	inline void SetScale(const float4& _scale)
	{
		scaleMode_ = RenderScaleMode::User;
		renderScale_ = _scale;
	}
	inline void SetTransColor(unsigned int _color)
	{
		TransColor_ = _color;
	}
	inline GameEngineImage* GetImage()
	{
		return image_;
	}

	void SetImageScale();
	void SetImage(const std::string& _name);
	void SetIndex(const size_t _index, float4 _scale = { -1.0, -1.0 });

protected:
	void Render();

private:
	GameEngineImage* image_;
	RenderPivot pivotType_;
	RenderScaleMode scaleMode_;
	float4 renderPivot_;
	float4 renderScale_;

	float4 renderImageScale_;
	float4 renderImagePivot_;

	unsigned int TransColor_;

	/////////////////////////////////////////// 애니메이션
private:
	class FrameAnimation
	{
	public:
		GameEngineRenderer* renderer_;
		GameEngineImage* image_;
		int currentFrame_;
		int startFrame_;
		int endFrame_;
		float currentInterTime_;
		float interTime_;
		bool loop_;

	public:
		FrameAnimation()
			: renderer_(nullptr)
			, image_(nullptr)
			, currentFrame_(-1)
			, startFrame_(-1)
			, endFrame_(-1)
			, currentInterTime_(0.1f)
			, interTime_(0.1f)
			, loop_(true)
		{
		}
		~FrameAnimation()
		{
		}

	public:
		void Update();

		inline void Reset()
		{
			currentFrame_ = startFrame_;
			currentInterTime_ = interTime_;
		}
	};

public:
	void CreateAnimation(const std::string& _image, const std::string& _name, int _startIndex, int _endIndex, float _interTime, bool _loop = true);
	void ChangeAnimation(const std::string& _name);

private:
	std::map<std::string, FrameAnimation> animations_;
	FrameAnimation* currentAnimation_;
};

