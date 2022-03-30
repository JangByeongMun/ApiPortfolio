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
	
	bool Create(HDC _DC);
	bool Create(float4 _Scale);
	bool Load(const std::string& _Path);

	inline float4 GetScale() const
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}
	inline HDC ImageDC() const
	{
		return ImageDC_;
	}

	void BitCopy(const GameEngineImage* _Other);
	void BitCopy(const GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenter(const GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenterPivot(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopyBot(const GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyBotPivot(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopy(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot);

	void TransCopy(
		const GameEngineImage* _Other,
		const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot,
		const float4& _OtherScale,
		unsigned int _TransColor 
	);

	void Cut(const float4& _CutSize);
	void CutCount(int _x, int _y);

	inline bool IsCut()
	{
		return 0 != CutPivot_.size();
	}
	inline float4 GetCutPivot(size_t _Index)
	{
		return CutPivot_[_Index];
	}
	inline float4 GetCutScale(size_t _Index)
	{
		return CutScale_[_Index];
	}
	inline void Cut(const float4& _CutScale, const float4& _CutPos)
	{
		CutPivot_.push_back(_CutPos);
		CutScale_.push_back(_CutScale);
	}

protected:

private:
	HDC ImageDC_;
	HBITMAP Bitmap_;
	HBITMAP OldBitmap_;
	BITMAP Info_;

	std::vector<float4> CutPivot_;
	std::vector<float4> CutScale_;

	void ImageScaleCheck();
};

