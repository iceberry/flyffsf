//#include <windows.h>
#include <stdio.h>
#include <afx.h>

//#include <afxwin.h>         // MFC core and standard components


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Aeonsoft");
LPCTSTR lpszWindowName = TEXT("Updater");
CString g_strCmdLine;

void Update();
void ErrorMsg();

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	TCHAR szArg1[64] = {0, }; 
	TCHAR szArg2[64] = {0, }; 
	TCHAR szArg3[64] = {0, }; 
	TCHAR szArg4[64] = {0, };

//	AfxMessageBox( lpszCmdParam );

	sscanf( lpszCmdParam, "%s %s %s %s", szArg1, szArg2, szArg3, szArg4 );
	if( strcmpi( szArg1, "myunglang" ) )
	{
		return 0; 
	}

	g_strCmdLine.Format("%s %s %s", szArg2, szArg3, szArg4);

	HWND hWnd;

	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszWindowName,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	//ShowWindow(hWnd,nCmdShow);
	hWndMain=hWnd;
	
	while(GetMessage(&Message,0,0,0)) 
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static DWORD ProcID = 0;
	static HANDLE hProc = 0;
	DWORD ExitCode;

	switch(iMessage) 
	{
	case ( WM_USER + 2 ): // recv SEND_PROCESSID from PatchMfcClient
		ProcID = wParam;
		hProc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, ProcID );
		GetExitCodeProcess( hProc, &ExitCode );
		if( ExitCode != STILL_ACTIVE )
		{
			// ��ȿ
			MessageBox( hWndMain, "�����ų �ڵ� ����", "����", MB_OK );
			//SetWindowText( hWndMain, "�׾���" );
		}
		else
		{
			// ��ȿ - ���� ����
			//MessageBox( hWndMain, "�ڵ� ����", "����", MB_OK );
			//SetWindowText( hWndMain, "���ϰ���" );
			TerminateProcess( hProc, 0 );
			//char msg[100]; wsprintf( msg, "%d", ret );
			WaitForSingleObject( hProc, INFINITE );
			Sleep(1500);
			CloseHandle( hProc );

//			MessageBox( hWndMain, "�����̴�", "����", MB_OK );
		}
		Update();
		return 0;
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

void Update()
{
	/*
	while( TRUE )
	{
		// ��ġ Ŭ���̾�Ʈ�� ������ ���� ������ �˾� ���� ����
		HANDLE hPatchStopEvent = OpenEvent( EVENT_MODIFY_STATE, FALSE, "PatchStopEvent" );
		if( NULL != hPatchStopEvent )
		{
			SetEvent( hPatchStopEvent );
			Sleep( 1000 );
			continue;
		}
		else
		{
			break;
		}
	}
	*/
	
	DWORD dwFileAttributes	= GetFileAttributes( "NewFlyff.exe" );
	if( 0xFFFFFFFF != dwFileAttributes )
	{
		dwFileAttributes &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( "NewFlyff.exe", dwFileAttributes );
	}
	dwFileAttributes	= GetFileAttributes( "Flyff.exe" );
	if( 0xFFFFFFFF != dwFileAttributes )
	{
		dwFileAttributes &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( "Flyff.exe", dwFileAttributes );
	}

	// ���� ���� ��ġŬ���̾�Ʈ�� �ִ°�
	HANDLE hNewFile = CreateFile( "NewFlyff.exe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( INVALID_HANDLE_VALUE == hNewFile )
	{
		ErrorMsg();
		//MessageBox( hWndMain, "NewPatchClinetn.exe ���� ����", "����", MB_OK );
		PostQuitMessage( 0 );
		return;
	}
	CloseHandle( hNewFile );

	// ���� ��ġŬ���̾�Ʈ�� ����
	if( FALSE == DeleteFile( "Flyff.exe" ) )
	{
		ErrorMsg();
		MessageBox( hWndMain, "Flyff.exe", "����", MB_OK );
		PostQuitMessage( 0 );
		return;
	}

	// ���� ���� ��ġŬ���̾�Ʈ�� ���ϸ� ����
	if( 0 != rename( "NewFlyff.exe", "Flyff.exe" ) )
	{
		ErrorMsg();
		//MessageBox( hWndMain, "������ ������ �� �����ϴ�", "����", MB_OK );
		PostQuitMessage( 0 );
		return;
	}

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	
	// ��ġ Ŭ���̾�Ʈ �� ����
//	if( FALSE == CreateProcess( NULL, "Flyff.exe 1", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
	CString strCmd;
	strCmd.Format("Flyff.exe %s", g_strCmdLine);

//	AfxMessageBox( strCmd );

	if( FALSE == CreateProcess( NULL, strCmd.GetBuffer(0), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
	{
		//MessageBox( hWndMain, "Masquerade.exe ���� ����", "����", MB_OK );
		ErrorMsg();
		PostQuitMessage( 0 );
		return;
	}

	PostQuitMessage( 0 );
}

void ErrorMsg()
{
	char szMsg[1024];
	char szErrorMsg[1024];
	
	DWORD dwErr = GetLastError();
	
	FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErr, 0, szErrorMsg, 1024, NULL );
	wsprintf( szMsg, "�����ڵ� : %d, �޽��� : %s", dwErr, szErrorMsg );
	MessageBox( hWndMain, szMsg, "����", MB_OK );
}