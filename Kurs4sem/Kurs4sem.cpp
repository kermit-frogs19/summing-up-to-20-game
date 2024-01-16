// Kurs4sem.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Kurs4sem.h"
#include <math.h>
#include <string>

#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

//Global creation of button handles to use them when we need to hide specific button
HWND buttonContinue;
HWND buttonNewGame;
HWND buttonExit;
HWND buttonGame1first;
HWND buttonGame2first;
HWND buttonGame3first;
HWND buttonGame1second;
HWND buttonGame2second;
HWND buttonGame3second;
HWND buttonBackHome;

bool isPlaying = false;
bool isThereAnySavedGames = false;
int totalGameCount = 0;
const wchar_t* totalGameCountSTR;
int winner = 0;
int whoMakesaMoveNow = 1;
bool winnerScreen;
bool didUserClickedContinue = false;
int winsCount = 0;
bool isStillInGame = false;

//handles for drawing and changing game screens
HFONT hFont;
HFONT hOldFont;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    InstructWnd(HWND, UINT, WPARAM, LPARAM);


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
    LoadStringW(hInstance, IDC_KURS4SEM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KURS4SEM));
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

    return (int)msg.wParam;
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
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KURS4SEM));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KURS4SEM);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
        CW_USEDEFAULT, 0, 820, 800, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    buttonContinue = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"Продовжити",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        20, 570, 240, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)1,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );


    buttonNewGame = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"Нова Гра",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        280, 570, 240, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)2,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );

    buttonExit = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"Вихід",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        540, 570, 240, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)3,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );

    buttonGame1first = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"1",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        125, 550, 150, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)4,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );
    ShowWindow(buttonGame1first, SW_HIDE);

    buttonGame2first = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"2",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        325, 550, 150, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)5,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );
    ShowWindow(buttonGame2first, SW_HIDE);

    buttonGame3first = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"3",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        525, 550, 150, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)6,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );
    ShowWindow(buttonGame3first, SW_HIDE);


    buttonGame1second = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"1",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        125, 40, 150, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)7,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );
    ShowWindow(buttonGame1second, SW_HIDE);

    buttonGame2second = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"2",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        325, 40, 150, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)8,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );
    ShowWindow(buttonGame2second, SW_HIDE);

    buttonGame3second = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"3",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        525, 40, 150, 150,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)9,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );
    ShowWindow(buttonGame3second, SW_HIDE);

    buttonBackHome = CreateWindow(
        L"BUTTON",                      // Predefined class name
        L"На Головну",                    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        300, 390, 200, 100,                // Position and size
        hWnd,                           // Parent window handle
        (HMENU)10,                       // Button identifier
        hInstance,                      // Instance handle
        NULL                            // No additional data
    );
    ShowWindow(buttonBackHome, SW_HIDE);

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

        switch (LOWORD(wParam))
        {
        case 1:
            didUserClickedContinue = true;   
            if ((winsCount > 0) && (isStillInGame == false))
            {
                totalGameCount = 0;
            }



        case 2:
            if (didUserClickedContinue == false)
            {
                totalGameCount = 0;
                whoMakesaMoveNow = 1;

                if (winner == 0)
                {
                    EnableWindow(buttonGame1first, FALSE);
                    EnableWindow(buttonGame2first, FALSE);
                    EnableWindow(buttonGame3first, FALSE);
                    EnableWindow(buttonGame1second, FALSE);
                    EnableWindow(buttonGame2second, FALSE);
                    EnableWindow(buttonGame3second, FALSE);
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                }
            }
            isPlaying = true;
            isStillInGame = true;
            ShowWindow(buttonExit, SW_HIDE);
            ShowWindow(buttonNewGame, SW_HIDE);
            ShowWindow(buttonContinue, SW_HIDE);
            ShowWindow(buttonGame1first, SW_SHOW);
            ShowWindow(buttonGame2first, SW_SHOW);
            ShowWindow(buttonGame3first, SW_SHOW);
            ShowWindow(buttonGame1second, SW_SHOW);
            ShowWindow(buttonGame2second, SW_SHOW);
            ShowWindow(buttonGame3second, SW_SHOW);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

            break;

        case 3:
            PostQuitMessage(0);
            break;

        case 4:
            totalGameCount += 1;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;

        case 5:
            totalGameCount += 2;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;

        case 6:
            totalGameCount += 3;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;

        case 7:
            totalGameCount += 1;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;

        case 8:
            totalGameCount += 2;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;

        case 9:
            totalGameCount += 3;

            break;

        case 10:
            isPlaying = false;
            winnerScreen = false;
            didUserClickedContinue = false;
            ShowWindow(buttonExit, SW_SHOW);
            ShowWindow(buttonNewGame, SW_SHOW);
            ShowWindow(buttonContinue, SW_SHOW);
            ShowWindow(buttonBackHome, SW_HIDE);
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

            break;
        }
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

        

        if (whoMakesaMoveNow == 1)
        {
            EnableWindow(buttonGame1second, FALSE);
            EnableWindow(buttonGame2second, FALSE);
            EnableWindow(buttonGame3second, FALSE);
            whoMakesaMoveNow = 2;
            EnableWindow(buttonGame1first, TRUE);
            EnableWindow(buttonGame2first, TRUE);
            EnableWindow(buttonGame3first, TRUE);
        }
        else
        {
            EnableWindow(buttonGame1first, FALSE);
            EnableWindow(buttonGame2first, FALSE);
            EnableWindow(buttonGame3first, FALSE);
            whoMakesaMoveNow = 1;
            EnableWindow(buttonGame1second, TRUE);
            EnableWindow(buttonGame2second, TRUE);
            EnableWindow(buttonGame3second, TRUE);
        }

        if ((LOWORD(wParam) == 4) || (LOWORD(wParam) == 5) || (LOWORD(wParam) == 6) || (LOWORD(wParam) == 7) || (LOWORD(wParam) == 8) || (LOWORD(wParam) == 9))
        {
            if (((totalGameCount > 20) && (whoMakesaMoveNow == 1)) || ((totalGameCount == 20) && (whoMakesaMoveNow == 2)))
            {
                winner = 2;
                winnerScreen = true;
                winsCount += 1;
                isStillInGame = false;
                EnableWindow(buttonGame1first, FALSE);
                EnableWindow(buttonGame2first, FALSE);
                EnableWindow(buttonGame3first, FALSE);
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            }

            if (((totalGameCount == 20) && (whoMakesaMoveNow == 1)) || ((totalGameCount > 20) && (whoMakesaMoveNow == 2)))
            {
                winner = 1;
                winnerScreen = true;
                winsCount += 1;
                isStillInGame = false;
                EnableWindow(buttonGame1second, FALSE);
                EnableWindow(buttonGame2second, FALSE);
                EnableWindow(buttonGame3second, FALSE);
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            }
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
        }


        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT_PROG:
            DestroyWindow(hWnd);
            break;

        case IDM_GAME_INSTRUCTION:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, InstructWnd);
            break;

        case IDM_MAINSCREEN:
            isPlaying = false;
            winnerScreen = false;
            didUserClickedContinue = false;
            ShowWindow(buttonExit, SW_SHOW);
            ShowWindow(buttonNewGame, SW_SHOW);
            ShowWindow(buttonContinue, SW_SHOW);            
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            //MessageBox(hWnd, L"Menu Button Test!", L"Button Example", MB_OK);
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
        // Get the client area dimensions
        RECT rect;
        GetClientRect(hWnd, &rect);
        // Set the line color to purple
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(128, 0, 128));
        HGDIOBJ hOldPen = SelectObject(hdc, hPen);

        // Draw the line
        MoveToEx(hdc, 2, 2, nullptr);
        LineTo(hdc, rect.right - 2, rect.top + 2);
        MoveToEx(hdc, rect.right - 2, rect.top + 2, nullptr);
        LineTo(hdc, rect.right - 2, rect.bottom - 2);
        MoveToEx(hdc, rect.right - 2, rect.bottom - 2, nullptr);
        LineTo(hdc, 2, rect.bottom - 2);
        MoveToEx(hdc, 2, rect.bottom - 2, nullptr);
        LineTo(hdc, 2, 2);

        // Set up the font for the arc text
        LOGFONT lf;
        ZeroMemory(&lf, sizeof(LOGFONT));
        lf.lfHeight = 70;  // Specify the desired font height
        lf.lfWeight = FW_NORMAL;
        wcscpy_s(lf.lfFaceName, LF_FACESIZE, L"Arial");  // Specify the desired font face name
        hFont = CreateFontIndirect(&lf);
        hOldFont = (HFONT)SelectObject(hdc, hFont);
        // Set text color and background mode
        SetTextColor(hdc, RGB(0, 0, 0));  // Black text color
        SetBkMode(hdc, TRANSPARENT);     // Transparent background


        //switch used variables
        int centerX, centerY, radius, textLength, textLength2, textLengthCount, startAngle, sweepAngle, centerminusX, x1, y1, x, y;
        const wchar_t* text = L"ПІДСУМОВУВАННЯ";
        const wchar_t* text2 = L"ДО2О";
        const wchar_t* text3 = L"РАХУНОК:22";
        const wchar_t* text4 = L"ПЕРЕМІГ";
        const wchar_t* text5 = L"ПЕРШИЙ ГРАВЕЦЬ";
        const wchar_t* text6 = L"ДРУГИЙ ГРАВЕЦЬ";
        double angleStep;
        centerX = (rect.right + rect.left) / 2;
        centerY = (rect.bottom + rect.top) / 2;
        std::wstring wstr = std::to_wstring(totalGameCount);
        totalGameCountSTR = wstr.c_str();
        textLengthCount = lstrlenW(totalGameCountSTR);


        switch (isPlaying)
        {
        case true:
            MoveToEx(hdc, 2, 320, nullptr);
            LineTo(hdc, rect.right - 2, 320);
            MoveToEx(hdc, 2, 420, nullptr);
            LineTo(hdc, rect.right - 2, 420);
            centerminusX = centerX - 180;
            x1 = centerminusX;
            y1 = centerY-35;

            if (winnerScreen == false)
            {
                lf.lfHeight = 20;
                hFont = CreateFontIndirect(&lf);
                hOldFont = (HFONT)SelectObject(hdc, hFont);
                TextOut(hdc, centerX - 65, 10, L"Другий Гравець", 15);
                TextOut(hdc, centerX - 65, rect.bottom - 30, L"Перший Гравець", 15);
                lf.lfHeight = 70;
                hFont = CreateFontIndirect(&lf);
                hOldFont = (HFONT)SelectObject(hdc, hFont);
                for (int i = 0; i < 8; i++)
                {
                    SelectObject(hdc, hFont);
                    SetTextColor(hdc, RGB(128, 0, 128));  // Purple color

                    TextOut(hdc, x1 - 2, y1, &text3[i], 1);
                    TextOut(hdc, x1 + 2, y1, &text3[i], 1);
                    TextOut(hdc, x1, y1 - 2, &text3[i], 1);
                    TextOut(hdc, x1, y1 + 2, &text3[i], 1);

                    SelectObject(hdc, hFont);
                    SetTextColor(hdc, RGB(255, 255, 255));  // White color
                    TextOut(hdc, x1, y1, &text3[i], 1);


                    x1 += 45;
                    if (i == 0) x1 -= 5;
                    if (i == 3) x1 -= 5;
                    if (i == 5) x1 += 3;
                    if (i == 6) x1 -= 5;
                    if (i == 7) x1 -= 20;
                    if (i == 8) x1 -= 7;
                }

                for (int i = 0; i < textLengthCount; i++)
                {
                    SelectObject(hdc, hFont);
                    SetTextColor(hdc, RGB(128, 0, 128));  // Purple color

                    TextOut(hdc, x1 - 2, y1, &totalGameCountSTR[i], 1);
                    TextOut(hdc, x1 + 2, y1, &totalGameCountSTR[i], 1);
                    TextOut(hdc, x1, y1 - 2, &totalGameCountSTR[i], 1);
                    TextOut(hdc, x1, y1 + 2, &totalGameCountSTR[i], 1);

                    SelectObject(hdc, hFont);
                    SetTextColor(hdc, RGB(255, 255, 255));  // White color
                    TextOut(hdc, x1, y1, &totalGameCountSTR[i], 1);
                    x1 += 35;
                }
            }
            else
            {
                hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
                hOldPen = SelectObject(hdc, hPen);
                MoveToEx(hdc, 2, 320, nullptr);
                LineTo(hdc, rect.right - 2, 320);
                MoveToEx(hdc, 2, 420, nullptr);
                LineTo(hdc, rect.right - 2, 420);
                hPen = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
                hOldPen = SelectObject(hdc, hPen);

                ShowWindow(buttonGame1first, SW_HIDE);
                ShowWindow(buttonGame2first, SW_HIDE);
                ShowWindow(buttonGame3first, SW_HIDE);
                ShowWindow(buttonGame1second, SW_HIDE);
                ShowWindow(buttonGame2second, SW_HIDE);
                ShowWindow(buttonGame3second, SW_HIDE);
                ShowWindow(buttonBackHome, SW_SHOW);
                centerminusX += 50;
                x1 = centerminusX;
                y1 -= 35;

                for (int i = 0; i < 7; i++)
                {
                    SelectObject(hdc, hFont);
                    SetTextColor(hdc, RGB(128, 0, 128));  // Purple color


                    TextOut(hdc, x1 - 2, y1, &text4[i], 1);
                    TextOut(hdc, x1 + 2, y1, &text4[i], 1);
                    TextOut(hdc, x1, y1 - 2, &text4[i], 1);
                    TextOut(hdc, x1, y1 + 2, &text4[i], 1);

                    SelectObject(hdc, hFont);
                    SetTextColor(hdc, RGB(255, 255, 255));  // White color
                    TextOut(hdc, x1, y1, &text4[i], 1);


                    x1 += 45;
                    if (i == 1) x1 -= 5;
                    if (i == 2) x1 -= 5;
                    if (i == 3) x1 -= 5;
                    if (i == 4) x1 += 5;
                    if (i == 5) x1 -= 30;

                }
                switch(winner)
                {
                case 1:                

                    centerminusX -= 160;
                    x1 = centerminusX;
                    y1 -= 70;
                    for (int i = 0; i < 14; i++)
                    {
                        SelectObject(hdc, hFont);
                        SetTextColor(hdc, RGB(128, 0, 128));  // Purple color

                        TextOut(hdc, x1 - 2, y1, &text5[i], 1);
                        TextOut(hdc, x1 + 2, y1, &text5[i], 1);
                        TextOut(hdc, x1, y1 - 2, &text5[i], 1);
                        TextOut(hdc, x1, y1 + 2, &text5[i], 1);

                        SelectObject(hdc, hFont);
                        SetTextColor(hdc, RGB(255, 255, 255));  // White color
                        TextOut(hdc, x1, y1, &text5[i], 1);


                        x1 += 45;
                        if (i == 1) x1 -= 5;
                        if (i == 2) x1 -= 5;
                        if (i == 3) x1 += 12;
                        if (i == 6) x1 -= 10;
                        if (i == 7) x1 -= 5;
                        if (i == 8) x1 -= 5;
                        if (i == 10) x1 -= 5;
                        if (i == 11) x1 -= 5;
                        if (i == 12) x1 += 2;
                    }
                    break;

                case 2:
                
                    centerminusX -= 160;
                    x1 = centerminusX;
                    y1 -= 70;
                    for (int i = 0; i < 14; i++)
                    {
                        SelectObject(hdc, hFont);
                        SetTextColor(hdc, RGB(128, 0, 128));  // Purple color

                        TextOut(hdc, x1 - 2, y1, &text6[i], 1);
                        TextOut(hdc, x1 + 2, y1, &text6[i], 1);
                        TextOut(hdc, x1, y1 - 2, &text6[i], 1);
                        TextOut(hdc, x1, y1 + 2, &text6[i], 1);

                        SelectObject(hdc, hFont);
                        SetTextColor(hdc, RGB(255, 255, 255));  // White color
                        TextOut(hdc, x1, y1, &text6[i], 1);


                        x1 += 45;
                        if (i == 1) x1 -= 5;
                        if (i == 2) x1 -= 5;
                        if (i == 3) x1 -= 10;
                        if (i == 6) x1 -= 10;
                        if (i == 7) x1 -= 5;
                        if (i == 8) x1 -= 5;
                        if (i == 10) x1 -= 5;
                        if (i == 11) x1 -= 5;
                        if (i == 12) x1 += 2;

                    }
                    break;
                
                }
            }
            
            break;

        case false:
            ShowWindow(buttonGame1first, SW_HIDE);
            ShowWindow(buttonGame2first, SW_HIDE);
            ShowWindow(buttonGame3first, SW_HIDE);
            ShowWindow(buttonGame1second, SW_HIDE);
            ShowWindow(buttonGame2second, SW_HIDE);
            ShowWindow(buttonGame3second, SW_HIDE);
            // Calculate the radius and center point for the arc            
            radius = (rect.right - rect.left) / 3.5;  // Adjust the radius as needed

            // Draw text along the arc with purple border
            textLength = lstrlenW(text);
            textLength2 = lstrlenW(text2);
            startAngle = 0;  // Start angle in degrees
            sweepAngle = 180;  // Sweep angle in degrees
            angleStep = static_cast<double>(sweepAngle) / (textLength - 1);

            for (int i = textLength - 1; i >= 0; --i)
            {
                // Draw the text with purple border
                x = centerX + static_cast<int>(radius * cos((startAngle + (textLength - 1 - i) * angleStep) * 3.14159 / 180.0));
                y = centerY - static_cast<int>(radius * sin((startAngle + (textLength - 1 - i) * angleStep) * 3.14159 / 180.0));

                // Set up the font and color for the purple border
                SelectObject(hdc, hFont);
                SetTextColor(hdc, RGB(128, 0, 128));  // Purple color

                // Draw the text with the purple border
                TextOut(hdc, x - 2, y, &text[i], 1);
                TextOut(hdc, x + 2, y, &text[i], 1);
                TextOut(hdc, x, y - 2, &text[i], 1);
                TextOut(hdc, x, y + 2, &text[i], 1);

                // Set up the font and color for the text
                SelectObject(hdc, hFont);
                SetTextColor(hdc, RGB(255, 255, 255));  // White text color

                // Draw the actual text
                TextOut(hdc, x, y, &text[i], 1);
            }

            centerminusX = centerX - 80;
            x1 = centerminusX;
            y1 = centerY;
            for (int i = 0; i < 4; i++)
            {
                SelectObject(hdc, hFont);
                SetTextColor(hdc, RGB(128, 0, 128));  // Purple color

                TextOut(hdc, x1 - 2, y1, &text2[i], 1);
                TextOut(hdc, x1 + 2, y1, &text2[i], 1);
                TextOut(hdc, x1, y1 - 2, &text2[i], 1);
                TextOut(hdc, x1, y1 + 2, &text2[i], 1);

                SelectObject(hdc, hFont);
                SetTextColor(hdc, RGB(255, 255, 255));  // White color
                TextOut(hdc, x1, y1, &text2[i], 1);

                if (i == 1) x1 += 20;
                x1 += 45;
                if (i == 2) x1 -= 5;

            }
            break;
        }
        

        // Cleanup
        EndPaint(hWnd, &ps);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
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

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK InstructWnd(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

