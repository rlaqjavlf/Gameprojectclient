
// socClientDlg.h : 헤더 파일
//

#pragma once
#include "ClientSocket.h"
#include "afxwin.h"

// CsocClientDlg 대화 상자
class CsocClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CsocClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private :
	CClientSocket m_ClientSocket;
	
	//맴버변수 생성
public:
	CListBox m_list_msg;
	CEdit m_edit_send;

	//버튼 이벤트
	afx_msg void OnClickedButtonSend();

protected : //사용자 메세지 지정함수
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

	
	/*아이피 바꾸기*/
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
