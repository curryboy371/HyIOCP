#include "pch.h"

#include "framework.h"
#include "ClientWinAPI.h"
#include <iostream>
#include <string>

#include "ClientWin.h"
#include "UserManager.h"
#include "User.h"
#include "ClientPacketHandler.h"

#include "Room.h"

#include "NetworkManager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND hEditInput;    // 입력 창 핸들
HWND hEditOutput;   // 출력 창 핸들
WNDPROC oldEditProc; // 입력 창의 원래 프로시저

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    EditProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


LRESULT CALLBACK ChatDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        if (wmId == IDC_MAIN_BUTTON_LOGIN)
        {

            HySessionRef mySession = GCinstance->GetManager<NetworkManager>()->Get_mySession();

            // 텍스트 받아서
            TCHAR username[256];
            TCHAR password[256];
            GetDlgItemText(hDlg, IDC_MAIN_EDIT_USERNAME, username, 256);
            GetDlgItemText(hDlg, IDC_MAIN_EDIT_PASSWORD, password, 256);

            std::string name = ConvertUTF8(username);
            std::string passwd = ConvertUTF8(password);

            // cb
            std::function<void(int32)> cbFund = [hDlg](int32 result) {
                // 성공 시 채팅 창으로 이동
                if (result == 0)
                {
                    MessageBox(hDlg, L"로그인 성공", L"알림", MB_OK);
                    EndDialog(hDlg, IDOK);
                }
                else
                {
                    MessageBox(hDlg, L"로그인 실패", L"알림", MB_OK);
                }
            };

            // 로그인 체크
            GCinstance->GetManager<NetworkManager>()->Send_CS_LOGIN(mySession, name, passwd, cbFund);

            // 로그인 성공시 
            // 입력 창에 포커스 설정
            //SetFocus(hEditInput);
        }
        else if (wmId == IDC_MAIN_BUTTON_REGISTER)
        {
            HySessionRef mySession = GCinstance->GetManager<NetworkManager>()->Get_mySession();

            // 텍스트 받아서
            TCHAR username[256];
            TCHAR password[256];
            GetDlgItemText(hDlg, IDC_MAIN_EDIT_USERNAME, username, 256);
            GetDlgItemText(hDlg, IDC_MAIN_EDIT_PASSWORD, password, 256);
            std::string name = ConvertUTF8(username);
            std::string passwd = ConvertUTF8(password);

            // cb
            std::function<void(int32)> cbFund = [hDlg](int32 result) {
                // 성공 시 
                if (result == 0)
                {
                    MessageBox(hDlg, L"회원가입 완료", L"알림", MB_OK);
                }
                else
                {
                    MessageBox(hDlg, L"회원가입 실패", L"알림", MB_OK);
                }
            };

            GCinstance->GetManager<NetworkManager>()->Send_CS_REGIST(mySession, name, passwd, cbFund);
        }
    }
    break;

    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}


LRESULT CALLBACK ChatDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        if (wmId == IDC_CHAT_BUTTON_SEND)
        {
            // 채팅 메시지 보내기 처리 로직
            HWND hEdit = GetDlgItem(hDlg, IDC_CHAT_EDIT_MESSAGE);
            int len = GetWindowTextLength(hEdit);
            if (len > 0)
            {
                TCHAR* buffer = (TCHAR*)GlobalAlloc(GPTR, len + 1);
                GetWindowText(hEdit, buffer, len + 1);
                // 메시지를 채팅 목록에 추가
                HWND hList = GetDlgItem(hDlg, IDC_CHAT_LIST_MESSAGES);
                SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);
                // 입력창 초기화
                SetWindowText(hEdit, L"");
                GlobalFree(buffer);
            }
        }
    }
    break;

    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;

}



bool bvDebug = true;

void RedirectIOToConsole() {
    // 콘솔을 할당합니다.
    AllocConsole();

    // 표준 입출력 스트림을 콘솔에 연결합니다.
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
}

void WorkThread(std::shared_ptr<IOCPClient> iocpRef)
{
    while (true)
    {
        tlsEndTickCount = ::GetTickCount64() + 64; // 여기도 타임아웃을 설정해둔다고 보면 됨.
        iocpRef->ProcessIOCompletion(10);
        ThreadManager::ScheduleJobQueueWork(); // 예약된 일감 처리
        ThreadManager::JobQueueWork(); //타임아웃에 걸리면 글로벌 큐에 넣음
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // Get the command line arguments
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    if (argv == NULL) {
        MessageBox(NULL, L"CommandLineToArgvW failed", L"Error", MB_OK);
        return 1;
    }

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENTWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENTWINAPI));
    MSG msg;

    // Get command line arguments as a wide string
    LPWSTR cmdLine = GetCommandLineW();

    // Convert the command line to a list of arguments
    int32 sessionCount = 1;
    bool bIsDevMode = false;
    if (argc > 1)
    {
        sessionCount = std::stoi(argv[1]);
        bIsDevMode = true;
    }
    else
    {
        // 콘솔 창을 설정합니다.
        RedirectIOToConsole();
    }

    // 
    // 
     // 클라이언트는 서버와 연결하기 위해 ServerSession 사용
    SessionConfig<ServerSession> sessionConfig(L"127.0.0.1", 7777, E_SESSION_TYPE::E_SESSION_C2S, sessionCount, "Client");

    std::shared_ptr<IOCPClient> iocpRef = std::make_shared<IOCPClient>(sessionConfig.GetAddress(), sessionConfig.GetSessionFactory(), sessionConfig.Get_maxSessionCount(), sessionConfig.Get_nameRef());
    HyClientInstanceRef instance = std::make_shared<HyClientInstance>();
    instance->InitHyInstance();
    instance->Set_IocpRef(iocpRef);
    instance->Set_bIsDevMode(bIsDevMode);

    bool ret = iocpRef->InitIOCP();
    if (ret)
    {
        // lamda...
        Ginstance->Get_threadMgr()->LaunchThread([&iocpRef]()
            {
                WorkThread(iocpRef);
            }
        );
    }

    if (instance->Get_bIsDevMode())
    {
        // 애플리케이션 초기화를 수행합니다:
        if (!InitInstance(hInstance, nCmdShow))
        {
            return FALSE;
        }

        HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENTWINAPI));
        MSG msg;

        // 기본 메시지 루프입니다:
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    else
    {

        // 로그인 대화 상자를 표시합니다.
        if (DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc) == IDOK)
        {
            // 애플리케이션 초기화를 수행합니다:
            if (!InitInstance(hInstance, nCmdShow))
            {
                return FALSE;
            }

            // lamda...
            Ginstance->Get_threadMgr()->LaunchThread([&iocpRef]()
                {
                    while (true)
                    {
                        //if (bvDebug)
                        {
                            std::this_thread::sleep_for(std::chrono::seconds(15));

                            Protocol::CS_ECHO echoptk;
                            std::string time = TimeManager::GetCurrentTimeAsString();
                            echoptk.set_msg("CS_ECHO... " + time);
                            auto sendBuffer = ClientPacketHandler::MakeSendBuffer(echoptk);

                            GCinstance->Get_room()->DoAsync([=] { GCinstance->Get_room()->Broadcast(sendBuffer); });
                        }

                    }

                }
            );



            HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENTWINAPI));
            MSG msg;

            // 기본 메시지 루프입니다:
            while (GetMessage(&msg, nullptr, 0, 0))
            {
                if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }


            return (int)msg.wParam;
        }
    }

    Ginstance->Get_threadMgr()->JoinThreads();
    instance->ReleaseInstance();

    return 0;
   // return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENTWINAPI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENTWINAPI);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 700, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 입력 창 생성
    hEditInput = CreateWindowEx(
        0, L"EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
        10, 540, 780, 25, // 입력 창 크기 지정
        hWnd, (HMENU)1, hInstance, NULL);

    // 출력 창 생성
    hEditOutput = CreateWindowEx(
        0, L"EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        10, 10, 780, 520, // 출력 창 크기 지정
        hWnd, NULL, hInstance, NULL);

    // 타이머 설정 (100ms)
    SetTimer(hWnd, 1, 60, NULL);


    return TRUE;
}

std::string ConvertUTF8(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

std::wstring ConvertUTF8(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.from_bytes(str);
}

void AddTextToOutput(const std::wstring& text) {

    std::string msg = ConvertUTF8(text);
    std::wstring wmsg = std::wstring().assign(msg.begin(), msg.end());

    int length = GetWindowTextLength(hEditOutput);
    SendMessage(hEditOutput, EM_SETSEL, length, length);
    SendMessage(hEditOutput, EM_REPLACESEL, 0, (LPARAM)wmsg.c_str());
    SendMessage(hEditOutput, EM_REPLACESEL, 0, (LPARAM)L"\r\n");

}

void AddTextToOutput(const std::string& text) {

    std::wstring wmsg = ConvertUTF8(text);

    int length = GetWindowTextLength(hEditOutput);
    SendMessage(hEditOutput, EM_SETSEL, length, length);
    SendMessage(hEditOutput, EM_REPLACESEL, 0, (LPARAM)wmsg.c_str());
    SendMessage(hEditOutput, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
}

void SendUserMessage(const std::wstring& text)
{
    Protocol::CS_CHAT chatpkt;

    std::string msg = ConvertUTF8(text);
    chatpkt.set_msg(msg);

    SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(chatpkt);
    GCinstance->Get_room()->DoAsync([sendBuffer]() { GCinstance->GetManager<UserManager>()->GetMyUser()->Get_ownerSessionRef()->PreSend(sendBuffer); });
}

void SendUserMessage(const std::string& text)
{
    Protocol::CS_CHAT chatpkt;
    chatpkt.set_msg(text);
    SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(chatpkt);
    GCinstance->Get_room()->DoAsync([sendBuffer]() { GCinstance->GetManager<UserManager>()->GetMyUser()->Get_ownerSessionRef()->PreSend(sendBuffer); });

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_TIMER:
    {
        // 타이머 이벤트에서 Enter 키를 검사합니다.
        if (GetFocus() == hEditInput) {
            if (GetKeyState(VK_RETURN) & 0x8000) {
                wchar_t buffer[256];
                GetWindowText(hEditInput, buffer, 256);
                if (wcslen(buffer) > 0) {

                    std::wstring str = buffer;
                    SendUserMessage(str);
                    //AddTextToOutput(buffer);
                    SetWindowText(hEditInput, L""); // 입력 창 비우기
                }
            }
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1); // 타이머 해제
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
