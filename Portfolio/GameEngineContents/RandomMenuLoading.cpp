#include "RandomMenuLoading.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsGlobal.h"

RandomMenuLoading::RandomMenuLoading() 
{
}

RandomMenuLoading::~RandomMenuLoading() 
{
}

void RandomMenuLoading::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	CreateRenderer("bgblack.bmp", RenderPivot::CENTER, { 0, 0 });

	LoadingRenderers_.push_back(CreateRenderer("loadimages-001.bmp", RenderPivot::CENTER, { 0, 0 }));
	LoadingRenderers_.push_back(CreateRenderer("loadimages-002.bmp", RenderPivot::CENTER, { 0, 0 }));
	LoadingRenderers_.push_back(CreateRenderer("loadimages-003.bmp", RenderPivot::CENTER, { 0, 0 }));
	LoadingRenderers_.push_back(CreateRenderer("loadimages-004.bmp", RenderPivot::CENTER, { 0, 0 }));
	LoadingRenderers_.push_back(CreateRenderer("loadimages-005.bmp", RenderPivot::CENTER, { 0, 0 }));
	LoadingRenderers_.push_back(CreateRenderer("loadimages-006.bmp", RenderPivot::CENTER, { 0, 0 }));
}

void RandomMenuLoading::RandomLoading()
{
	GameEngineSoundPlayer TmpPlayer = GameEngineSound::SoundPlayControlOneShot("MenuLoadingSound.ogg");
	TmpPlayer.SetVolume(0.5f * Option_MUSIC);

	GameEngineRandom TmpRandom;
	int SelectedIndex = TmpRandom.RandomInt(0, 5);
	for (int i = 0; i < 6; i++)
	{
		if (i == SelectedIndex)
		{
			LoadingRenderers_[i]->On();
		}
		else
		{
			LoadingRenderers_[i]->Off();
		}
	}
}

