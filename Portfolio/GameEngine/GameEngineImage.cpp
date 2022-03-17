#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
	: imageDC_(nullptr)
	, bitmap_(nullptr)
	, oldBitmap_(nullptr)
	, info_()
{
}

GameEngineImage::~GameEngineImage() 
{
}

bool GameEngineImage::Create(float4 _scale)
{
	if (true == _scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
		return false;
	}

	imageDC_ = CreateCompatibleDC(nullptr);
	bitmap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _scale.ix(), _scale.iy());
	
	if (nullptr == imageDC_)
	{
		MsgBoxAssert("imageDC_ 생성에 실패 했습니다.");
	}
	oldBitmap_ = (HBITMAP)SelectObject(imageDC_, bitmap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck() 
{
	GetObject(bitmap_, sizeof(BITMAP), &info_);
}

