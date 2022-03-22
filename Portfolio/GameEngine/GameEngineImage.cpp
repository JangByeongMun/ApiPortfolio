#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage() 
	: imageDC_(nullptr)
	, bitmap_(nullptr)
	, oldBitmap_(nullptr)
	, info_()
{
}

GameEngineImage::~GameEngineImage() 
{
	if (nullptr != bitmap_)
	{
		DeleteObject(bitmap_);
		bitmap_ = nullptr;
	}

	if (nullptr != oldBitmap_)
	{
		DeleteObject(oldBitmap_);
		oldBitmap_ = nullptr;
	}

	if (nullptr != imageDC_)
	{
		DeleteDC(imageDC_);
		imageDC_ = nullptr;
	}
}

bool GameEngineImage::Create(HDC _dc)
{
	imageDC_ = _dc;
	ImageScaleCheck();
	return true;
}

bool GameEngineImage::Create(float4 _scale)
{
	if (true == _scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
		return false;
	}

	bitmap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _scale.ix(), _scale.iy());
	if (nullptr == bitmap_)
	{
		MsgBoxAssert("bitmap_ 생성에 실패 했습니다.");
	}

	imageDC_ = CreateCompatibleDC(nullptr);
	if (nullptr == imageDC_)
	{
		MsgBoxAssert("imageDC_ 생성에 실패 했습니다.");
	}
	oldBitmap_ = (HBITMAP)SelectObject(imageDC_, bitmap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Load(const std::string& _path)
{
	bitmap_ = static_cast<HBITMAP>(LoadImageA(nullptr, _path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	if (nullptr	== bitmap_)
	{
		MsgBoxAssertString(_path + "이미지 로드에 실패 했습니다.");
		return false;
	}

	imageDC_ = CreateCompatibleDC(nullptr);
	if (nullptr == imageDC_)
	{
		MsgBoxAssert("imageDC_ 생성에 실패 했습니다.");
		return false;
	}
	oldBitmap_ = (HBITMAP)SelectObject(imageDC_, bitmap_);

	ImageScaleCheck();
	return true;
}

void GameEngineImage::BitCopy(const GameEngineImage* _other)
{
	BitCopy(_other, float4{ 0, 0 }, _other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopy(const GameEngineImage* _other, const float4& _copyPos)
{
	BitCopy(_other, _copyPos, _other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyCenter(const GameEngineImage* _other, const float4& _copyPos)
{
	BitCopy(_other, _copyPos - _other->GetScale().Half(), _other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyCenterPivot(const GameEngineImage* _other, const float4& _copyPos, const float4& _copyPivot)
{
	BitCopy(_other, _copyPos - _other->GetScale().Half() + _copyPivot, _other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyBot(const GameEngineImage* _other, const float4& _CopyPos)
{
	float4 ImagePivot = _other->GetScale().Half();
	ImagePivot.y = _other->GetScale().y;

	BitCopy(_other, _CopyPos - ImagePivot, _other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyBotPivot(const GameEngineImage* _other, const float4& _copyPos, const float4& _copyPivot)
{
	float4 ImagePivot = _other->GetScale().Half();
	ImagePivot.y = _other->GetScale().y;

	BitCopy(_other, _copyPos - ImagePivot + _copyPivot, _other->GetScale(), float4{ 0, 0 });
}
void BitCopy(const GameEngineImage* _other, const float4& _coplyPos, const float4& _copyScale, const float4& _otherPivot);
void GameEngineImage::BitCopy(const GameEngineImage* _other, const float4& _copyPos, const float4& _copyScale, const float4& _otherPivot)
{
	BitBlt
	(
		imageDC_,
		_copyPos.ix(),
		_copyPos.iy(),
		_copyScale.ix(),
		_copyScale.iy(),
		_other->imageDC_,
		_otherPivot.ix(),
		_otherPivot.iy(),
		SRCCOPY
	);
}

void GameEngineImage::TransCopyCenter(const GameEngineImage* _other, const float4& _copyPos, unsigned int _transColor)
{
	TransCopy(_other, _copyPos - _other->GetScale().Half(), _other->GetScale(), float4{ 0, 0 }, _other->GetScale(), _transColor);
}

void GameEngineImage::TransCopyCenterScale(GameEngineImage* _other, const float4& _copyPos, const float4& _renderScale, unsigned int _transColor)
{
	TransCopy(_other, _copyPos - _renderScale.Half(), _renderScale, float4{ 0, 0 }, _other->GetScale(), _transColor);
}

void GameEngineImage::TransCopy(const GameEngineImage* _other, const float4& _copyPos, const float4& _copyScale, const float4& _otherPivot, const float4& _otherScale, unsigned int _transColor)
{
	TransparentBlt
	(
		imageDC_,
		_copyPos.ix(),
		_copyPos.iy(),
		_copyScale.ix(),
		_copyScale.iy(),
		_other->imageDC_,
		_otherPivot.ix(),
		_otherPivot.iy(),
		_otherScale.ix(),
		_otherScale.iy(),
		_transColor
	);
}

void GameEngineImage::ImageScaleCheck()
{
	HBITMAP currentBitMap = (HBITMAP)GetCurrentObject(imageDC_, OBJ_BITMAP);
	GetObject(bitmap_, sizeof(BITMAP), &info_);
}