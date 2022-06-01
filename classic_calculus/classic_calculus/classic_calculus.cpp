// classic_calculus.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "classic_calculus.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Calculus(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Calculus2(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Calculus3(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Calculus4(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLASSICCALCULUS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLASSICCALCULUS));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLASSICCALCULUS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLASSICCALCULUS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_CALCULUS1:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CALCULUS1), hWnd, Calculus);
                break;
            case IDM_CALCULUS2:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CALCULUS2), hWnd, Calculus2);
                break;
            case IDM_CALCULUS3:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CALCULUS3), hWnd, Calculus3);
                break;
            case IDM_CALCULUS4:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CALCULUS4), hWnd, Calculus4);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
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

// окно с первым калькулятором 
INT_PTR CALLBACK Calculus(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    // получаем окно вывода
    HWND field_answer = GetDlgItem(hDlg, 1003);

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
            if (LOWORD(wParam) == IDC_CALCULATE1) {
                num1 = GetDlgItemInt(hDlg, 1000, NULL, false);
                num2 = GetDlgItemInt(hDlg, 1001, NULL, false);
                num3 = GetDlgItemInt(hDlg, 1002, NULL, false);
                
                //int result = calculate_sum(field1_text, field2_text, field3_text);
                std::string answer = calculate_sum(num1, num2, num3);
                SetWindowTextA(field_answer, answer.c_str());
                //MessageBoxA(hDlg, GetWindowTextA(field1), "msg", MB_OK);
                return (INT_PTR)TRUE;
            }
            break;


    }
    
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Calculus2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    // получаем окна вывода и операций
    HWND field_answer = GetDlgItem(hDlg, IDC_EDIT14);
    HWND operation1 = GetDlgItem(hDlg, IDC_EDIT15);
    HWND operation2 = GetDlgItem(hDlg, IDC_EDIT16);


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
        if (LOWORD(wParam) == IDC_CALCULATE2) {

            num1 = GetDlgItemInt(hDlg, IDC_EDIT11, NULL, false);
            num2 = GetDlgItemInt(hDlg, IDC_EDIT12, NULL, false);
            num3 = GetDlgItemInt(hDlg, IDC_EDIT13, NULL, false);

            GetWindowTextA(operation1, c2_op1, 2);
            GetWindowTextA(operation2, c2_op2, 2);

            std::string op1 = std::string(c2_op1);
            std::string op2 = std::string(c2_op2);

            if ((good_op(op1) == (std::string("0"))) || (good_op(op2) == (std::string("0")))) {
                MessageBoxA(hDlg, std::string("только + - * :").c_str(), "msg", MB_OK);
            }
            else {
                std::string answer = calculate_second(num1, num2, num3, op1, op2);
                SetWindowTextA(field_answer, answer.c_str());
            }
            //MessageBoxA(hDlg, std::to_string(num1).c_str(), "msg", MB_OK);
            return (INT_PTR)TRUE;
        }
        break;


    }

    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK Calculus3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    // получаем окна вывода и операций
    HWND field_answer = GetDlgItem(hDlg, IDC_EDIT22);
    HWND text_input = GetDlgItem(hDlg, IDC_EDIT21);

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
        if (LOWORD(wParam) == IDC_CALCULATE3) {

            GetWindowTextA(text_input, c3_input, 79);

            std::string input = std::string(c3_input);
            MessageBoxA(hDlg, reverse_polish(input).c_str(), "g", MB_OK);
            MessageBoxA(hDlg, calc_reverse(reverse_polish(input)).c_str(), "o", MB_OK);
            //std::string result = calc3(input);
            SetWindowTextA(field_answer, calc_reverse(reverse_polish(input)).c_str());

            return (INT_PTR)TRUE;
        }
        break;


    }

    return (INT_PTR)FALSE;
}


std::string generated = "3+2";
INT_PTR CALLBACK Calculus4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    // получаем окна вывода и операций
    HWND field_answer = GetDlgItem(hDlg, IDC_EDIT31);
    HWND user_input = GetDlgItem(hDlg, IDC_EDIT32);
    HWND check_ans = GetDlgItem(hDlg, IDC_EDIT33);

    //std::string true_answer = calc3(generated);

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        //Generate
        SetWindowTextA(field_answer, generated.c_str());
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDC_CALCULATE4) {
            SetWindowTextA(field_answer, generated.c_str());
            std::string true_answer = calc3(generated);

            GetWindowTextA(user_input, c4_input, 79);
            if (std::stof(std::string(c4_input)) - 0.1 < std::stof(true_answer) && 
                std::stof(std::string(c4_input)) + 0.1 > std::stof(true_answer) ) {
                MessageBoxA(hDlg, "good", "g", MB_OK);
                SetWindowTextA(check_ans, "CORRECTO");
                generated = generate_polish();

            }
            else {
                SetWindowTextA(check_ans, "INCORRECTO");
            }
            SetWindowTextA(field_answer, generated.c_str());
            //SetWindowTextA(check_ans, "checked");

            return (INT_PTR)TRUE;
        }
        break;


    }

    return (INT_PTR)FALSE;
}
