#pragma once

// 설명 : 아이작을 따라다니는 펫
class Familiar
{
public:
	// constrcuter destructer
	Familiar();
	~Familiar();

	// delete Function
	Familiar(const Familiar& _Other) = delete;
	Familiar(Familiar&& _Other) noexcept = delete;
	Familiar& operator=(const Familiar& _Other) = delete;
	Familiar& operator=(Familiar&& _Other) noexcept = delete;

protected:

private:

};

