#pragma once

enum class CharacterType
{
	isaac,

};


// Ό³Έν :
class CharacterTypeManager
{
private:
	static CharacterTypeManager* inst_;
public:
	static CharacterTypeManager* GetInst();
	static void Destroy();

	void SetCharacterType();
protected:

private:
	CharacterType type_;


	CharacterTypeManager();
	~CharacterTypeManager();
	CharacterTypeManager(const CharacterTypeManager& _Other) = delete;
	CharacterTypeManager(CharacterTypeManager&& _Other) noexcept = delete;
	CharacterTypeManager& operator=(const CharacterTypeManager& _Other) = delete;
	CharacterTypeManager& operator=(CharacterTypeManager&& _Other) noexcept = delete;
};

