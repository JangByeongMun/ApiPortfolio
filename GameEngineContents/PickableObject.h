#pragma once

// 설명 : 주울수있는 아이템들 (하트, 카드, 열쇠, 폭탄 등)
class PickableObject
{
public:
	// constrcuter destructer
	PickableObject();
	~PickableObject();

	// delete Function
	PickableObject(const PickableObject& _Other) = delete;
	PickableObject(PickableObject&& _Other) noexcept = delete;
	PickableObject& operator=(const PickableObject& _Other) = delete;
	PickableObject& operator=(PickableObject&& _Other) noexcept = delete;

protected:

private:

};

