#include "BindingOfIsaac.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <conio.h>

BindingOfIsaac::BindingOfIsaac() 
{
}

BindingOfIsaac::~BindingOfIsaac() 
{
}

void BindingOfIsaac::GameInit()
{
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");
}

int testI = 0;
void BindingOfIsaac::GameLoop()
{
	++testI;
	if (testI >= 10)
	{
		ChangeLevel("Play");
	}
	int a = 0;
}

void BindingOfIsaac::GameEnd()
{
	int a = 0;
}
