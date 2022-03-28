#include "MenuLevel.h"
#include "MenuUI.h"

MenuLevel::MenuLevel() 
{
}

MenuLevel::~MenuLevel() 
{
}

void MenuLevel::Loading()
{
	CreateActor<MenuUI>(0);
}

void MenuLevel::Update()
{
}

void MenuLevel::LevelChangeStart()
{
}

void MenuLevel::LevelChangeEnd()
{
}
