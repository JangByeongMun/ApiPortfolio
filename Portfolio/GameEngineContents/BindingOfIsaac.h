#pragma once
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineEnum.h>

// ���� :
class BindingOfIsaac : public GameEngine
{
public:
	static CharacterType characterType;

	// constrcuter destructer
	BindingOfIsaac();
	~BindingOfIsaac();

	// delete Function
	BindingOfIsaac(const BindingOfIsaac& _Other) = delete;
	BindingOfIsaac(BindingOfIsaac&& _Other) noexcept = delete;
	BindingOfIsaac& operator=(const BindingOfIsaac& _Other) = delete;
	BindingOfIsaac& operator=(BindingOfIsaac&& _Other) noexcept = delete;

protected:
	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

private:
	void ImageLoad();
	void ImageCut();
};

