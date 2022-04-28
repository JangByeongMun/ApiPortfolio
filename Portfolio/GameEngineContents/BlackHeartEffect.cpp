#include "BlackHeartEffect.h"
#include <GameEngineBase/GameEngineTime.h>
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Player.h"

BlackHeartEffect::BlackHeartEffect() 
	: Renderer_(nullptr)
	, AnimTimer_(0.0f)
	, IsDestroy_(false)
	, StartPos_(float4::ZERO)
{
}

BlackHeartEffect::~BlackHeartEffect() 
{
}

void BlackHeartEffect::Start()
{
	Renderer_ = CreateRenderer("giantbook_rebirth_002_blackheart.bmp", static_cast<int>(ORDER::FRONTUI));
	Renderer_->SetScale({ 320, 320 });
	Renderer_->SetAlpha(0);
	AnimTimer_ = 0.0f;
}

void BlackHeartEffect::Update()
{
	if (StartPos_.CompareInt2D(float4::ZERO))
	{
		StartPos_ = GetPosition();
	}

	AnimTimer_ += GameEngineTime::GetDeltaTime();


	if (AnimTimer_ <= 0.5f)
	{
		float4 LerpScale = float4::Lerp({ 320, 320 }, {640, 640}, AnimTimer_ * 2.0f);
		Renderer_->SetScale(LerpScale);

		unsigned int LerpAlpha = static_cast<unsigned int>(float4::LerpFloat(0.0f, 255.0f, AnimTimer_ * 2.0f));
		Renderer_->SetAlpha(LerpAlpha);
	}
	else if (AnimTimer_ <= 0.6f)
	{
		SetPosition(StartPos_ + float4(-5, 0));
	}
	else if (AnimTimer_ <= 0.7f)
	{
		SetPosition(StartPos_ + float4(5, 0));
	}
	else if (AnimTimer_ <= 0.8f)
	{
		SetPosition(StartPos_ + float4(-5, 0));
	}
	else if (AnimTimer_ <= 0.9f)
	{
		SetPosition(StartPos_ + float4(5, 0));
	}
	else if (AnimTimer_ <= 1.0f)
	{
		SetPosition(StartPos_ + float4(-5, 0));
	}
	else if (AnimTimer_ <= 1.3f)
	{
		SetPosition(StartPos_);

		float4 LerpScale = float4::Lerp({ 640, 640 }, { 960, 960 }, (AnimTimer_ - 1.0f) * 4.0f);
		Renderer_->SetScale(LerpScale);

		unsigned int LerpAlpha = static_cast<unsigned int>(float4::LerpFloat(0.0f, 255.0f, AnimTimer_ * 2.0f));
		Renderer_->SetAlpha(LerpAlpha);

		if (false == IsDestroy_)
		{
			IsDestroy_ = true;
			Player::MainPlayer->BlackHeartDestroy();
		}
	}
	else if (AnimTimer_ <= 1.4f)
	{
		Death();
	}
}

