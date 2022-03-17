#pragma once
#include <Windows.h>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class GameEngineImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;
	
	bool Create(float4 _scale);
	inline float4 Scale()
	{
		return float4(static_cast<float>(info_.bmWidth), static_cast<float>(info_.bmHeight));
	}
	inline HDC ImageDC()
	{
		return imageDC_;
	}

protected:

private:
	HDC imageDC_;
	HBITMAP bitmap_;
	HBITMAP oldBitmap_;
	BITMAP info_;

	void ImageScaleCheck();
};

