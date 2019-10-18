
// socClientDlg.h : ��� ����
//

#pragma once
#include "ClientSocket.h"
#include "afxwin.h"

// CsocClientDlg ��ȭ ����
class CsocClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CsocClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private :
	CClientSocket m_ClientSocket;
	
	//�ɹ����� ����
public:
	CListBox m_list_msg;
	CEdit m_edit_send;

	//��ư �̺�Ʈ
	afx_msg void OnClickedButtonSend();

protected : //����� �޼��� �����Լ�
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientCountRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPlayerPortNumRecv(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnEnemy1ValueRecv(WPARAM wParam, LPARAM lParam);
	afx_msg
		LRESULT OnEnemyValueRecv(WPARAM wParam, LPARAM lParam);
	LRESULT OnEnemy2ValueRecv(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnPlayResultRecv(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnEnChangeEditSend();

	
	/*������ �ٲٱ�*/
	CString m_edit_ip;
	afx_msg void OnClickedButtonCon();
	afx_msg void OnEnChangeEditIp();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonRock();
	afx_msg void OnClickedButtonPaper();
	afx_msg void OnClickedButtonScissors();

	bool m_start;

	afx_msg void OnChangeEditCount();
	CString m_Client_Count;
	int m_StartCount;
	int m_choice;
	afx_msg void OnChangeEditChoice();
	CString m_choice_msg;
	void OnImagePrint();
	void OnImagePrint2();
	bool m_ClickCheck;
	int m_PlayerPortNum;
	afx_msg void OnEnChangeEditMyportnum();
	CString m_MyPortNum_Msg;
	int m_Player2PortNum;
	int m_EnemyChoice1;
	int m_EnemyChoice2;
	bool m_Swich1;
	bool m_Swich2;
};
