#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

// Ό³Έν :
class MenuFileSelect : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuFileSelect();
	~MenuFileSelect();

	// delete Function
	MenuFileSelect(const MenuFileSelect& _Other) = delete;
	MenuFileSelect(MenuFileSelect&& _Other) noexcept = delete;
	MenuFileSelect& operator=(const MenuFileSelect& _Other) = delete;
	MenuFileSelect& operator=(MenuFileSelect&& _Other) noexcept = delete;

	void ChangeFile(int _Index);

	inline int GetCurrentIndex() const
	{
		return CurrentIndex_;
	}

protected:

private:
	std::vector<GameEngineRenderer*> AllFiles_;
	std::vector<float4> AllPos_;
	int CurrentIndex_;
	int NextIndex_;
	bool IsChange;
	float CurrentTime_;
	float ChangeTime_;

	void Start() override;
	void Update() override;
};

