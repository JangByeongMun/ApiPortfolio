#include "GameEngineWindow.h"
#include "GameEngineDebug.h"
#include <assert.h>
#include <Windows.h>
#include "GameEngineInput.h"

LRESULT CALLBACK GameEngineWindow::MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        GameEngineWindow::GetInst().Off();
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CLOSE:
    {
        GameEngineWindow::GetInst().Off();
        break;
    }
    case WM_MOUSEWHEEL:
    {
        GameEngineInput::GetInst()->WheelValue = (SHORT)HIWORD(wParam);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    // 윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    if (nullptr != hWnd_)
    {
        MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst; 
    RegClass(_hInst);

    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    hDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow()
{ 
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다 화면에 출력할수 없습니다.");
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;

    while (WindowOn_)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 여기서 내부 구현
        
        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    Scale_ = _Scale;
    RECT rect = { 0, 0, static_cast<long>(_Scale.x), static_cast<long>(_Scale.y)};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
}

GameEngineWindow::GameEngineWindow()
    : Title_("")
    , hInst_(nullptr)
    , hWnd_(nullptr)
    , WindowOn_(true)
    , hDC_(nullptr)
    , Scale_()
{
}

GameEngineWindow::~GameEngineWindow()
{
    // hInst_는 싱글톤이고 직접 삭제해준다. 
    // + 아래쪽 dc와 window는 각각 함수로 제거해야되고 순서대로 해야 문제가 없다.

    if (nullptr != hDC_)
    {
        ReleaseDC(hWnd_, hDC_);
        hDC_ = nullptr;
    }
    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

