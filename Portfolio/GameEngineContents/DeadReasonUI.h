#pragma once

// ���� : ���� ������ ǥ�����ִ�â
class DeadReasonUI
{
public:
	// constrcuter destructer
	DeadReasonUI();
	~DeadReasonUI();

	// delete Function
	DeadReasonUI(const DeadReasonUI& _Other) = delete;
	DeadReasonUI(DeadReasonUI&& _Other) noexcept = delete;
	DeadReasonUI& operator=(const DeadReasonUI& _Other) = delete;
	DeadReasonUI& operator=(DeadReasonUI&& _Other) noexcept = delete;

protected:

private:

};

