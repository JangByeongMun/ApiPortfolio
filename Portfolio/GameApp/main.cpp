#include <Windows.h>
#include <GameEngineContents/BindingOfIsaac.h>
#include <GameEngineBase/GameEngineFile.h>

// main�Լ��� �����ε� �ؼ� ����Ѱ�
// �⺻ win ������Ʈ�� ����� wWinMain���� �����µ� �� w�� �����ڵ��� �ǹ��̰� ��Ƽ����Ʈ�� ����ϱ����� w�� �� ������ ���
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ char* lpCmdLine, // �⺻������ wchar_t* ���� ������ �ڷ����� ���µ� ������ ��Ƽ����Ʈ�� �ٲ����Ƿ� char*�� ����
					_In_ int nCmdShow)
{

	GameEngineFile NewFile = "D:\\aaa.tt";
	NewFile.Open(OpenMode::Write);
	
	GameEngine::Start<BindingOfIsaac>();
}