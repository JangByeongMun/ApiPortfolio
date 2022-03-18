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
	imageDC_ = CreateCompatibleDC(nullptr);
	
	if (nullptr == imageDC_)
	{
		MsgBoxAssert("imageDC_ 생성에 실패 했습니다.");
	}
	oldBitmap_ = (HBITMAP)SelectObject(imageDC_, bitmap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::BitCopy(GameEngineImage* _other)
{
	BitCopy(_other, { 0, 0 }, { 0, 0 }, _other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _other, const float4& _coplyPos, const float4& _otherPivot, const float4& _otherPivotScale)
{
	BitBlt
	(
		imageDC_,
		_coplyPos.ix(),
		_coplyPos.iy(),
		_otherPivotScale.ix(),
		_otherPivotScale.iy(),
		_other->imageDC_,
		_otherPivot.ix(),
		_otherPivot.iy(),
		SRCCOPY
	);
}

void GameEngineImage::ImageScaleCheck()
{
	HBITMAP currentBitMap = (HBITMAP)GetCurrentObject(imageDC_, OBJ_BITMAP);
	GetObject(bitmap_, sizeof(BITMAP), &info_);
}

