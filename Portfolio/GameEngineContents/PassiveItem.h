#pragma once

// 설명 : 먹을수 있는 패시브 아이템
class PassiveItem
{
public:
	// constrcuter destructer
	PassiveItem();
	~PassiveItem();

	// delete Function
	PassiveItem(const PassiveItem& _Other) = delete;
	PassiveItem(PassiveItem&& _Other) noexcept = delete;
	PassiveItem& operator=(const PassiveItem& _Other) = delete;
	PassiveItem& operator=(PassiveItem&& _Other) noexcept = delete;

protected:

private:

};

