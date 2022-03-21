#pragma once
#include "GameEngineImage.h"
#include "GameEngineEnum.h"

// Ό³Έν :
class GameEngineRenderer
{
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
	void SetImage(const std::string& _name);
	void Render();
	float4 GetPosition();

protected:

private:
	GameEngineImage* image_;
	RenderPivot pivotType_;
};

