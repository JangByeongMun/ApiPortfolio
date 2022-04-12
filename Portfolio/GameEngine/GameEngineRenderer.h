#pragma once
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// 설명 :
class GameEngineImage;
class GameEngineFolderImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;
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
	inline RenderPivot GetPivotType()
	{
		return PivotType_;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}
	inline RenderScaleMode GetScaleMode()
	{
		return ScaleMode_;
	}

	inline void SetPivot(const float4& _Pivot)
	{
		RenderPivot_ = _Pivot;
	}
	inline float4 GetPivot()
	{
		return RenderPivot_;
	}

	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}
	inline float4 GetScale()
	{
		return RenderPivot_;
	}

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}
	inline unsigned int GetTransColor()
	{
		return TransColor_;
	}

	inline void SetAlpha(unsigned int _Alpha)
	{
		Alpha_ = _Alpha;

		if (Alpha_ >= 255)
		{
			Alpha_ = 255;
		}
	}
	inline unsigned int GetAlpha()
	{
		return Alpha_;
	}

	void SetImageScale();
	void SetImage(const std::string& _Name);
	void SetIndex(const size_t _Index, const float4& _Scale = { -1.0f, -1.0f });

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}


	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}
	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}

	void SetOrder(int _Order) override;

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_;
	RenderScaleMode ScaleMode_;
	
	// 화면에 출력할 좌표와 크기
	float4 RenderPivot_;
	float4 RenderScale_;

	// 잘라낼 좌표와 크기
	float4 RenderImageScale_;
	float4 RenderImagePivot_;

	unsigned int TransColor_;
	unsigned int Alpha_;
	bool IsCameraEffect_;

	/////////////////////////////////////////// 애니메이션
private:
	friend class FrameAnimation;
	class FrameAnimation : public GameEngineNameObject
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;

		int TimeKey_;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_;
		bool IsEnd_;

	public:
		FrameAnimation()
			: Renderer_(nullptr)
			, Image_(nullptr)
			, FolderImage_(nullptr)
			, TimeKey_(0)
			, CurrentFrame_(-1)
			, StartFrame_(-1)
			, EndFrame_(-1)
			, CurrentInterTime_(0.1f)
			, InterTime_(0.1f)
			, Loop_(true)
			, IsEnd_(false)
		{
		}
		~FrameAnimation()
		{
		}

	public:
		void Update();

		inline void Reset()
		{
			IsEnd_ = false;
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}
	};

public:
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void CreateAnimationTimeKey(const std::string& _image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void ChangeAnimation(const std::string& _Name);

	bool IsEndAnimation();
	bool IsAnimationName(const std::string& _Name);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};

