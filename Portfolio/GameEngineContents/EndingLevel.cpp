#include "EndingLevel.h"
#include "EndingBackGround.h"
#include "Credit01.h"
#include "Credit02.h"
#include "Credit03.h"
#include "Credit04.h"
#include "Credit05.h"
#include "Credit06.h"
#include "Credit07.h"
#include "Credit08.h"
#include "Credit09.h"
#include "Credit10.h"

EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::Loading()
{
}

void EndingLevel::Update()
{
}

void EndingLevel::LevelChangeStart()
{
	CreateActor<EndingBackGround>(0);
	//CreateActor<Credit01>(1);
	//CreateActor<Credit02>(1);
	//CreateActor<Credit03>(1);
	//CreateActor<Credit04>(1);
	//CreateActor<Credit05>(1);
	//CreateActor<Credit06>(1);
	//CreateActor<Credit07>(1);
	//CreateActor<Credit08>(1);
	//CreateActor<Credit09>(1);
	CreateActor<Credit10>(1);
}

void EndingLevel::LevelChangeEnd()
{
	
}

