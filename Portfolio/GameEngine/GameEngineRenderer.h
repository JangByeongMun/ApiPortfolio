#pragma once
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// ���� :
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
	
	// ȭ�鿡 ����� ��ǥ�� ũ��
	float4 RenderPivot_;
	float4 RenderScale_;

	// �߶� ��ǥ�� ũ��
	float4 RenderImageScale_;
	float4 RenderImagePivot_;

	unsigned int TransColor_;
	bool IsCameraEffect_;

	/////////////////////////////////////////// �ִϸ��̼�
private:
	friend class FrameAnimation;
	class FrameAnimation : public GameEngineNameObject
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;

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
	void CreateAnimation(const std::string& _image, const std::string& _name, int _startIndex, int _endIndex, float _interTime, bool _loop = true);
	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);
	void ChangeAnimation(const std::string& _name);

	bool IsEndAnimation();
	bool IsAnimationName(const std::string& _Name);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};

