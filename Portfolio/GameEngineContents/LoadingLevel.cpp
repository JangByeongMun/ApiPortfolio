#include "LoadingLevel.h"
#include "LoadingPage.h"
#include "LoadingCharacter.h"
#include "LoadingMap.h"
#include "LoadingBubble.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "PlayLevel.h"
#include "BindingOfIsaac.h"
#include "ContentsGlobal.h"

LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Loading()
{
	CreateActor<LoadingPage>(0);
	CreateActor<LoadingCharacter>(1);
	CreateActor<LoadingBubble>(1);
	CreateActor<LoadingMap>(2);
}

void LoadingLevel::Update()
{
}