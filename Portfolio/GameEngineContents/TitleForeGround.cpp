#include "TitleForeGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

TitleForeGround::TitleForeGround()
	: Renderer_(nullptr)
{
}

TitleForeGround::~TitleForeGround() 
{
}

void TitleForeGround::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());

	Renderer_ = CreateRenderer("Titleshadow.bmp", RenderPivot::CENTER, { -260, 135 }, 10);
	Renderer_->SetAlpha(20);
	Renderer_->CameraEffectOff();
}

