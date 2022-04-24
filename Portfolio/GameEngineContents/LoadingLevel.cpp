#include "LoadingLevel.h"
#include "LoadingPage.h"
#include "LoadingCharacter.h"
#include "LoadingMap.h"
#include "LoadingBubble.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "PlayLevel.h"
#include "BindingOfIsaac.h"

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

	GameEngineInput::GetInst()->CreateKey("Test", 'R');
}

void LoadingLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Test"))
	{
		BindingOfIsaac* TmpEngine = dynamic_cast<BindingOfIsaac*>(&GameEngine::GetInst());
		if (nullptr != TmpEngine)
		{
			TmpEngine->ResetPlayLevel("Play");
			TmpEngine->ChangeLevel("Play");
		}
	}
}