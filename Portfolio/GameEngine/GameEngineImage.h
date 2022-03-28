#pragma once
#include <Windows.h>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <vector>

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

	void TransCopy(
		const GameEngineImage* _other,
		const float4& _copyPos,
		const float4& _copyScale,
		const float4& _otherPivot,
		const float4& _otherScale,
		unsigned int _transColor 
	);

	void Cut(const float4& _cutSize);
	inline bool IsCut()
	{
		return 0 != cutPivot_.size();
	}
	inline float4 GetCutPivot(size_t _Index)
	{
		return cutPivot_[_Index];
	}
	inline float4 GetCutScale(size_t _Index)
	{
		return cutScale_[_Index];
	}
	inline void Cut(const float4& _CutScale, const float4& _CutPos)
	{
		cutPivot_.push_back(_CutPos);
		cutScale_.push_back(_CutScale);
	}

protected:

private:
	HDC imageDC_;
	HBITMAP bitmap_;
	HBITMAP oldBitmap_;
	BITMAP info_;

	std::vector<float4> cutPivot_;
	std::vector<float4> cutScale_;

	void ImageScaleCheck();
};

