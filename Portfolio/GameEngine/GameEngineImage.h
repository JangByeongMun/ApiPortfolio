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
	
	bool Create(HDC _dc);
	bool Create(float4 _scale);
	bool Load(const std::string& _path);

	inline float4 GetScale() const
	{
		return float4(static_cast<float>(info_.bmWidth), static_cast<float>(info_.bmHeight));
	}
	inline HDC ImageDC() const
	{
		return imageDC_;
	}

	void BitCopy(const GameEngineImage* _other);
	void BitCopy(const GameEngineImage* _other, const float4& _copyPos);
	void BitCopyCenter(const GameEngineImage* _other, const float4& _copyPos);
	void BitCopyCenterPivot(const GameEngineImage* _other, const float4& _copyPos, const float4& _copyPivot);
	void BitCopyBot(const GameEngineImage* _other, const float4& _copyPos);
	void BitCopyBotPivot(const GameEngineImage* _other, const float4& _copyPos, const float4& _copyPivot);
	void BitCopy(const GameEngineImage* _other, const float4& _copyPos, const float4& _copyScale, const float4& _otherPivot);

	void TransCopyCenter(const GameEngineImage* _other, const float4& _copyPos, unsigned int _transColor);
	void TransCopyCenterScale(GameEngineImage* _other, const float4& _copyPos, const float4& _renderScale, unsigned int _transColor);
	void TransCopy(const GameEngineImage* _other, const float4& _copyPos,
		const float4& _copyScale, const float4& _otherPivot,
		const float4& _otherScale, unsigned int _transColor );
protected:

private:
	HDC imageDC_;
	HBITMAP bitmap_;
	HBITMAP oldBitmap_;
	BITMAP info_;

	void ImageScaleCheck();
};

