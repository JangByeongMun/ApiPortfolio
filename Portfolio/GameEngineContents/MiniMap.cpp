#include "MiniMap.h"
#include <GameEngine/GameEngineRenderer.h>
#include "RandomRoomManager.h"
#include "RoomActor.h"

MiniMap::MiniMap() 
{
}

MiniMap::~MiniMap() 
{
}

void MiniMap::Start()
{
	SetPosition({ 1150, 100 });

	CreateRenderer("minimap_Frame.bmp")->CameraEffectOff();
	GameEngineRenderer* Renderer = CreateRenderer("minimap_BG.bmp");
	Renderer->CameraEffectOff();
	Renderer->SetAlpha(100);
}

void MiniMap::Update()
{
}

