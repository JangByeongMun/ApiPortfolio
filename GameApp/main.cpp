#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineContents/BindingOfIsaac.h>

// main함수를 오버로딩 해서 사용한것
// 기본 win 프로젝트를 만들면 wWinMain으로 나오는데 이 w는 유니코드라는 의미이고 멀티바이트를 사용하기위해 w를 뺀 버전을 사용
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ char* lpCmdLine, // 기본적으로 wchar_t* 형의 디파인 자료형을 썻는데 위에서 멀티바이트로 바꼈으므로 char*로 변경
					_In_ int nCmdShow)
{
	GameEngine::Start<BindingOfIsaac>();
}