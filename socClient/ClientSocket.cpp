// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "socClient.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{

}

CClientSocket::~CClientSocket()
{
}



// CClientSocket 멤버 함수 받는애
void CClientSocket::SetWnd(HWND hWnd) {
	m_hWnd = hWnd;
}




/*서버->클라이언트 받음*/
void CClientSocket::OnReceive(int nErrorCode) {
	int header[2]; //구분 
/****************************메세지 받는부분 *************************************/
	Receive((char *)header, sizeof(int) * 2);

	if (header[0] == 100) {//100이면 메세지
	MyMessage* msg = new MyMessage;
		CString strTmp = _T(""), strIPAddress = _T("");

		UINT uPortNumber = 0;
		//초기화작업
		ZeroMemory(msg->strBuffer, sizeof(msg->strBuffer));

		Receive((char *)msg, header[1]);
		GetPeerName(strIPAddress, uPortNumber);
		//여기선 내용만
		strTmp.Format(_T("%s"), msg->strBuffer);
		SendMessage(m_hWnd, WM_CLIENT_RECV, 0, (LPARAM)((LPCTSTR)strTmp));

	}
	else if (header[0] == 300) {
		//AfxMessageBox(_T("오냐"));
		MyCount* S_Count = new MyCount;

		//CString str; 
		//str.Format(_T("%d"), S_Count->OnCount);

		Receive((char *)S_Count, header[1]);

		SendMessage(m_hWnd, WM_Count_RECV, 0, (LPARAM)((int)S_Count->OnCount));

		delete S_Count;
	}

	// 포트번호 서버->클라이언트 
	else if (header[0] == 500) {

		MyPortNum* R_PortNum = new MyPortNum;

		Receive((char *)R_PortNum, header[1]);
		SendMessage(m_hWnd, WM_PlayerPort_RECV, 0, (LPARAM)(R_PortNum));
	
		delete R_PortNum;
	}
	/* 서버에서 보낸 최종 결과물 */
	else if (header[0] == 600) {
		MyResult* result = new MyResult;

		Receive((char *)result, header[1]);

		SendMessage(m_hWnd, WM_Result_RECV, 0, (LPARAM)(result));
		delete result;
	}
	else if (header[0] == 710) {
		MyEnemy1Value* E1_Value = new MyEnemy1Value;

		Receive((char *)E1_Value, header[1]);

		SendMessage(m_hWnd, WM_EnemyValue_RECV, 0, (LPARAM)(E1_Value));
	}


	else if (header[0] == 720) {
		MyEnemy2Value* E2_Value = new MyEnemy2Value;

		Receive((char *)E2_Value, header[1]);

		SendMessage(m_hWnd, WM_EnemyValue_RECV, 0, (LPARAM)(E2_Value));
	}





	CSocket::OnReceive(nErrorCode);
}




void CClientSocket::OnClose(int nErrorCode) {
	ShutDown();
	Close();
	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("서버꺼짐"));
	
	PostQuitMessage(0);
}
	/*
	else if (header[0] == 710) {
		MyEnemy1Value* E1_Value = new MyEnemy1Value;
		
		Receive((char *)E1_Value, header[1]);
		
		SendMessage(m_hWnd, WM_EnemyValue_RECV, 0, (LPARAM)(E1_Value));
	}


	else if (header[0]==720){
		MyEnemy2Value* E2_Value = new MyEnemy2Value;
		
		Receive((char *)E2_Value, header[1]);

		SendMessage(m_hWnd, WM_EnemyValue_RECV, 0, (LPARAM)(E2_Value));
	}
	
	/*
	else if (header[0] == 700) {
		MyEnemyValue* E_Value = new MyEnemyValue;

		Receive((char *)E_Value, header[1]);

		SendMessage(m_hWnd, WM_Enemy1Value_RECV, 0, (LPARAM)(E_Value));
	}
	*/