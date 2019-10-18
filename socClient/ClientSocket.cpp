// ClientSocket.cpp : ���� �����Դϴ�.
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



// CClientSocket ��� �Լ� �޴¾�
void CClientSocket::SetWnd(HWND hWnd) {
	m_hWnd = hWnd;
}




/*����->Ŭ���̾�Ʈ ����*/
void CClientSocket::OnReceive(int nErrorCode) {
	int header[2]; //���� 
/****************************�޼��� �޴ºκ� *************************************/
	Receive((char *)header, sizeof(int) * 2);

	if (header[0] == 100) {//100�̸� �޼���
	MyMessage* msg = new MyMessage;
		CString strTmp = _T(""), strIPAddress = _T("");

		UINT uPortNumber = 0;
		//�ʱ�ȭ�۾�
		ZeroMemory(msg->strBuffer, sizeof(msg->strBuffer));

		Receive((char *)msg, header[1]);
		GetPeerName(strIPAddress, uPortNumber);
		//���⼱ ���븸
		strTmp.Format(_T("%s"), msg->strBuffer);
		SendMessage(m_hWnd, WM_CLIENT_RECV, 0, (LPARAM)((LPCTSTR)strTmp));

	}
	else if (header[0] == 300) {
		//AfxMessageBox(_T("����"));
		MyCount* S_Count = new MyCount;

		//CString str; 
		//str.Format(_T("%d"), S_Count->OnCount);

		Receive((char *)S_Count, header[1]);

		SendMessage(m_hWnd, WM_Count_RECV, 0, (LPARAM)((int)S_Count->OnCount));

		delete S_Count;
	}

	// ��Ʈ��ȣ ����->Ŭ���̾�Ʈ 
	else if (header[0] == 500) {

		MyPortNum* R_PortNum = new MyPortNum;

		Receive((char *)R_PortNum, header[1]);
		SendMessage(m_hWnd, WM_PlayerPort_RECV, 0, (LPARAM)(R_PortNum));
	
		delete R_PortNum;
	}
	/* �������� ���� ���� ����� */
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

	AfxMessageBox(_T("��������"));
	
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