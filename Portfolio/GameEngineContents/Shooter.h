#pragma once

// 설명 : 투사체를 발사 하는 스크립트
class Shooter
{
public:
	// constrcuter destructer
	Shooter();
	~Shooter();

	// delete Function
	Shooter(const Shooter& _Other) = delete;
	Shooter(Shooter&& _Other) noexcept = delete;
	Shooter& operator=(const Shooter& _Other) = delete;
	Shooter& operator=(Shooter&& _Other) noexcept = delete;

protected:

private:

};

