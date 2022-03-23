#pragma once
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;
	
	void SetImage(const std::string& _name);
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
	void SetImageScale();
	inline void SetTransColor(unsigned int _color)
	{
		TransColor_ = _color;
	}

	void Render();

protected:

private:
	GameEngineImage* image_;
	RenderPivot pivotType_;
	RenderScaleMode scaleMode_;
	float4 renderPivot_;
	float4 renderScale_;
	unsigned int TransColor_;
};

