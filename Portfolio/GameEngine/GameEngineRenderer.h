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
	
	inline void SetPivotType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}
	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}
	inline void SetPivot(const float4& _Pivot)
	{
		RenderPivot_ = _Pivot;
	}
	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}
	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}
	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

	void SetImageScale();
	void SetImage(const std::string& _Name);
	void SetIndex(const size_t _Index, const float4& _Scale = { -1.0f, -1.0f });

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_;
	RenderScaleMode ScaleMode_;
	float4 RenderPivot_;
	float4 RenderScale_;
	float4 RenderImageScale_;
	float4 RenderImagePivot_;

	unsigned int TransColor_;
	bool IsCameraEffect_;

	/////////////////////////////////////////// 애니메이션
private:
	class FrameAnimation
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_;

	public:
		FrameAnimation()
			: Renderer_(nullptr)
			, Image_(nullptr)
			, CurrentFrame_(-1)
			, StartFrame_(-1)
			, EndFrame_(-1)
			, CurrentInterTime_(0.1f)
			, InterTime_(0.1f)
			, Loop_(true)
		{
		}
		~FrameAnimation()
		{
		}

	public:
		void Update();

		inline void Reset()
		{
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}
	};

public:
	void CreateAnimation(const std::string& _image, const std::string& _name, int _startIndex, int _endIndex, float _interTime, bool _loop = true);
	void ChangeAnimation(const std::string& _name);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};

