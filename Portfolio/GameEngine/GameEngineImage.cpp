#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

//#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage() 
	: ImageDC_(nullptr)
	, Bitmap_(nullptr)
	, OldBitmap_(nullptr)
	, Info_()
{
}

GameEngineImage::~GameEngineImage() 
{
	if (nullptr != Bitmap_)
	{
		DeleteObject(Bitmap_);
		Bitmap_ = nullptr;
	}

	if (nullptr != OldBitmap_)
	{
		DeleteObject(OldBitmap_);
		OldBitmap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteDC(ImageDC_);
		ImageDC_ = nullptr;
	}
}

bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;
	ImageScaleCheck();
	return true;
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
		return false;
	}

	Bitmap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	if (nullptr == Bitmap_)
	{
		MsgBoxAssert("bitmap_ 생성에 실패 했습니다.");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);
	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("imageDC_ 생성에 실패 했습니다.");
	}
	OldBitmap_ = (HBITMAP)SelectObject(ImageDC_, Bitmap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	Bitmap_ = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	if (nullptr	== Bitmap_)
	{
		MsgBoxAssertString(_Path + "이미지 로드에 실패 했습니다.");
		return false;
	}

	ImageDC_ = CreateCompatibleDC(nullptr);
	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("imageDC_ 생성에 실패 했습니다.");
		return false;
	}
	OldBitmap_ = (HBITMAP)SelectObject(ImageDC_, Bitmap_);

	ImageScaleCheck();
	return true;
}

void GameEngineImage::BitCopy(const GameEngineImage* _Other)
{
	BitCopy(_Other, float4{ 0, 0 }, _Other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopy(const GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyCenter(const GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyCenterPivot(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyBot(const GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopyBotPivot(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}
void GameEngineImage::BitCopy(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	BitBlt
	(
		ImageDC_,
		_CopyPos.ix(),
		_CopyPos.iy(),
		_CopyScale.ix(),
		_CopyScale.iy(),
		_Other->ImageDC_,
		_OtherPivot.ix(),
		_OtherPivot.iy(),
		SRCCOPY
	);
}

void GameEngineImage::TransCopy(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	TransparentBlt
	(
		ImageDC_,
		_CopyPos.ix(),
		_CopyPos.iy(),
		_CopyScale.ix(),
		_CopyScale.iy(),
		_Other->ImageDC_,
		_OtherPivot.ix(),
		_OtherPivot.iy(),
		_OtherScale.ix(),
		_OtherScale.iy(),
		_TransColor
	);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	if (0 != GetScale().ix() % _CutSize.ix())
	{
		MsgBoxAssert("자를수 있는 수치가 딱 맞지 않습니다.");
	}
	if (0 != GetScale().iy() % _CutSize.iy())
	{
		MsgBoxAssert("자를수 있는 수치가 딱 맞지 않습니다.");
	}

	int XCount = GetScale().ix() / _CutSize.ix();
	int YCount = GetScale().iy() / _CutSize.iy();
	for (int y = 0; y < YCount; y++)
	{
		for (int x = 0; x < XCount; x++)
		{
			CutPivot_.push_back({ static_cast<float>(x * _CutSize.ix()), static_cast<float>(y * _CutSize.iy()) });
			CutScale_.push_back(_CutSize);
		}
	}
}

void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

void GameEngineImage::ImageScaleCheck()
{
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(Bitmap_, sizeof(BITMAP), &Info_);
}