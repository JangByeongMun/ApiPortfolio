#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class OptionsMenu : public GameEngineActor
{
public:
	// constrcuter destructer
	OptionsMenu();
	~OptionsMenu();

	// delete Function
	OptionsMenu(const OptionsMenu& _Other) = delete;
	OptionsMenu(OptionsMenu&& _Other) noexcept = delete;
	OptionsMenu& operator=(const OptionsMenu& _Other) = delete;
	OptionsMenu& operator=(OptionsMenu&& _Other) noexcept = delete;

	void AddIndex(int _Index);
	void AddValue(int _Value);

protected:

private:
	std::vector<float4> ArrowPos_;
	GameEngineRenderer* Arrow_;
	int CurrentIndex_;

	GameEngineRenderer* VolumeSfx_;
	GameEngineRenderer* VolumeMusic_;
	GameEngineRenderer* VolumeMapOpacity_;

	void Start() override;
};

