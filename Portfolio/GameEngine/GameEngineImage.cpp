#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

//#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage() 
	: ImageDC_(nullptr)
	, BitMap_(nullptr)
	, OldBitmap_(nullptr)
	, Info_()
{
}

GameEngineImage::~GameEngineImage() 
{
	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
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

	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	if (nullptr == BitMap_)
	{
		MsgBoxAssert("bitmap_ 생성에 실패 했습니다.");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);
	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("imageDC_ 생성에 실패 했습니다.");
	}
	OldBitmap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	if (nullptr	== BitMap_)
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
	OldBitmap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();
	return true;
}

void GameEngineImage::BitCopy(const GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), { 0, 0 });
}
void GameEngineImage::BitCopy(const GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), { 0, 0 });
}
void GameEngineImage::BitCopyCenter(const GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), { 0, 0 });
}
void GameEngineImage::BitCopyCenterPivot(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), { 0, 0 });
}
void GameEngineImage::BitCopyBot(const GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), { 0, 0 });
}
void GameEngineImage::BitCopyBotPivot(const GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), { 0, 0 });
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

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
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

void GameEngineImage::AlphaCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot, const float4& _OtherScale, unsigned int _Alpha)
{
	BLENDFUNCTION Func;
	Func.BlendOp = AC_SRC_OVER;
	Func.BlendFlags = 0;
	Func.SourceConstantAlpha = _Alpha;
	Func.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
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
		Func 
	);
}

void GameEngineImage::PlgCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot, const float4& _OtherScale, float _Angle, GameEngineImage* _Filter)
{
	// 180도일때 버그가 생겨서 180도일때 조금 틀어서 버그 막도록 구현
	if (_Angle == 180.0f)
	{
		_Angle = 180.00001f;
	}

	POINT RotPoint[3];

	GameEngineRect Rect = GameEngineRect(float4::ZERO, _CopyScale);

	float4 LeftTop = Rect.CenterLeftTopPoint();
	float4 RightTop = Rect.CenterRightTopPoint();
	float4 LeftBot = Rect.CenterLeftBotPoint();
	float4 Center = _CopyPos + _CopyScale.Half();


	RotPoint[0] = (Rect.CenterLeftTopPoint().RotationToDegreeZ(_Angle) + Center).ToWinAPIPOINT();
	RotPoint[1] = (Rect.CenterRightTopPoint().RotationToDegreeZ(_Angle) + Center).ToWinAPIPOINT();
	RotPoint[2] = (Rect.CenterLeftBotPoint().RotationToDegreeZ(_Angle) + Center).ToWinAPIPOINT();

	PlgBlt(
		ImageDC_,
		RotPoint,
		_Other->ImageDC_,
		_OtherPivot.ix(), // 윈도우 이미지의 위치 x에서부터 y
		_OtherPivot.iy(), // 윈도우 이미지의 위치 x에서부터 y
		_OtherScale.ix(), // 내 이미지의 이 크기만큼 x
		_OtherScale.iy(), // 내 이미지의 이 크기만큼 y
		_Filter->BitMap_, // 복사하려는 대상은(거기에 그려지는 이미지가 뭔데?커비)
		_OtherPivot.ix(), // 복사하려는 대상의 시작점X 위치
		_OtherPivot.iy()  // 복사하려는 대상의 시작점Y
	);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	//if (0 != GetScale().ix() % _CutSize.ix())
	//{
	//	MsgBoxAssert("자를수 있는 수치가 딱 맞지 않습니다.");
	//}
	//if (0 != GetScale().iy() % _CutSize.iy())
	//{
	//	MsgBoxAssert("자를수 있는 수치가 딱 맞지 않습니다.");
	//}

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

int GameEngineImage::GetImagePixel(int _x, int _y)
{
	return GetPixel(ImageDC_, _x, _y);
}

void GameEngineImage::ImageScaleCheck()
{
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(BitMap_, sizeof(BITMAP), &Info_);
}