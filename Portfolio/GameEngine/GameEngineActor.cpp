#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine.h"
#include "GameEngineImageManager.h"

GameEngineActor::GameEngineActor() 
	: level_(nullptr)
	, position_()
	, scale_()
{
}

GameEngineActor::~GameEngineActor() 
{
}

void GameEngineActor::Start()
{
}

void GameEngineActor::Update()
{
}

void GameEngineActor::Render()
{
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(position_, scale_);
	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.GetCenterLeft(),
		DebugRect.GetCenterTop(),
		DebugRect.GetCenterRight(),
		DebugRect.GetCenterBot()
	);
}

void GameEngineActor::CreateRenderer(const std::string& _image, RenderPivot _pivotType, float4 _addPivot)
{
	GameEngineImage* findImage = GameEngineImageManager::GetInst()->Find(_image);
	if (nullptr == findImage)
	{
		MsgBoxAssert("플레이어 이미지를 찾지 못했습니다.");
		return;	
	}

	switch (_pivotType)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->BitCopyCenterPivot(findImage, GetPosition(), _addPivot);
		break;
	case RenderPivot::BOT:
		GameEngine::BackBufferImage()->BitCopyBotPivot(findImage, GetPosition(), _addPivot);
		break;
	default:
		break;
	}
}
