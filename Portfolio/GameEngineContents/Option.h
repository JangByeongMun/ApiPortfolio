#pragma once

// 설명 : esc키로 뜨는 옵션창
class Option
{
public:
	// constrcuter destructer
	Option();
	~Option();

	// delete Function
	Option(const Option& _Other) = delete;
	Option(Option&& _Other) noexcept = delete;
	Option& operator=(const Option& _Other) = delete;
	Option& operator=(Option&& _Other) noexcept = delete;

protected:

private:

};

