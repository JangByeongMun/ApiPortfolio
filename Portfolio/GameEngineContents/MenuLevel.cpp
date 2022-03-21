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
}

void MenuLevel::Update()
{
}

void MenuLevel::LevelChangeStart()
{
	CreateActor<MenuUI>("MenuUI", 0);
}

void MenuLevel::LevelChangeEnd()
{
}
