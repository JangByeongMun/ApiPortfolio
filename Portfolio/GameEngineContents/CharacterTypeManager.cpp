#include "CharacterTypeManager.h"

CharacterTypeManager* CharacterTypeManager::inst_ = new CharacterTypeManager();
CharacterTypeManager* CharacterTypeManager::GetInst()
{
	return inst_;
}

void CharacterTypeManager::Destroy()
{
	if (nullptr != inst_)
	{
		delete inst_;
		inst_ = nullptr;
	}
}

void CharacterTypeManager::SetCharacterType()
{
}

CharacterTypeManager::CharacterTypeManager()
{
}

CharacterTypeManager::~CharacterTypeManager() 
{
}

