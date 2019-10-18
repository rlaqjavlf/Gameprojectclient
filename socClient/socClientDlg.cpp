
// socClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "socClient.h"
#include "socClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define PORT 9999
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsocClientDlg ��ȭ ����



CsocClientDlg::CsocClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCCLIENT_DIALOG, pParent)
	, m_edit_ip(_T(""))
	, m_start(false)
	, m_Client_Count(_T(""))
	, m_StartCount()
	, m_choice(0)
	, m_choice_msg(_T(""))
	, m_ClickCheck(false)
	, m_PlayerPortNum(0)
	, m_MyPortNum_Msg(_T(""))
	, m_Player2PortNum(0)
	, m_EnemyChoice1(0)
	, m_EnemyChoice2(0)
	, m_Swich1(false)
	, m_Swich2(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsocClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);

	DDX_Text(pDX, IDC_EDIT_IP, m_edit_ip);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_Client_Count);

	DDX_Text(pDX, IDC_EDIT_Choice, m_choice_msg);
	DDX_Text(pDX, IDC_EDIT_MyPortNum, m_MyPortNum_Msg);
}

BEGIN_MESSAGE_MAP(CsocClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//IDC_BUTTON_SEND�� �Լ� OnClickedButtonSend�� ����ش� Ŭ���̾�Ʈ-> ������
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CsocClientDlg::OnClickedButtonSend)
	
	/*****************************************************************/
	//����->Ŭ���̾�Ʈ
	ON_MESSAGE(WM_CLIENT_RECV, &CsocClientDlg::OnClientRecv)
	ON_MESSAGE(WM_Count_RECV, &CsocClientDlg::OnClientCountRecv)
	ON_MESSAGE(WM_PlayerPort_RECV, &CsocClientDlg::OnPlayerPortNumRecv)
	ON_MESSAGE(WM_Result_RECV, &CsocClientDlg::OnPlayResultRecv)
	ON_MESSAGE(WM_EnemyValue_RECV, &CsocClientDlg::OnEnemyValueRecv)
	//ON_MESSAGE(WM_Enemy1Value_RECV, &CsocClientDlg::OnEnemy1ValueRecv)
	//ON_MESSAGE(WM_Enemy2Value_RECV, &CsocClientDlg::OnEnemy2ValueRecv)


	/*****************************************************************/
	ON_EN_CHANGE(IDC_EDIT_COUNT, &CsocClientDlg::OnChangeEditCount)
	ON_EN_CHANGE(IDC_EDIT_SEND, &CsocClientDlg::OnEnChangeEditSend)
	ON_BN_CLICKED(IDC_BUTTON_CON, &CsocClientDlg::OnClickedButtonCon)
	ON_EN_CHANGE(IDC_EDIT_IP, &CsocClientDlg::OnEnChangeEditIp)

	

	/*****************************************************************/
	ON_BN_CLICKED(IDC_BUTTON_START, &CsocClientDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_ROCK, &CsocClientDlg::OnClickedButtonRock)
	ON_BN_CLICKED(IDC_BUTTON_PAPER, &CsocClientDlg::OnClickedButtonPaper)
	ON_BN_CLICKED(IDC_BUTTON_SCISSORS, &CsocClientDlg::OnClickedButtonScissors)	
	ON_EN_CHANGE(IDC_EDIT_Choice, &CsocClientDlg::OnChangeEditChoice)
	ON_EN_CHANGE(IDC_EDIT_MyPortNum, &CsocClientDlg::OnEnChangeEditMyportnum)

END_MESSAGE_MAP()


// CsocClientDlg �޽��� ó����

BOOL CsocClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	//������ ���̵� �ּ� ���� �ʱ�ȭ �۾� 
	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	/*
	if (m_ClientSocket.Connect(_T("192.168.0.10"),PORT) == FALSE){
		
		AfxMessageBox(_T("==connect ����, �ּ��ʱ�ȭ ����=="));
		PostQuitMessage(0);
		return FALSE;
	}
	*/
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CsocClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CsocClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CsocClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsocClientDlg::OnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	UpdateData(true);
	
  //str ����ش�
	m_edit_send.GetWindowTextW(str);

	/*����ü�� �°� ������ ���ش� */
	ReceivMessages* temp = new ReceivMessages;
	temp->id = 100;
	temp->size = sizeof(MyMessage);
	//ī�Ǳ���ü�� �ִ� 
	_tcscpy(temp->msg.strBuffer, str);


	m_ClientSocket.Send((char *)temp, sizeof(MyMessage));
	//������ ������ �����ִ¿� 
	//m_ClientSocket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	
	m_edit_send.SetWindowTextW(_T(""));
	
	delete temp;
	UpdateData(FALSE);

}

afx_msg LRESULT CsocClientDlg::OnClientRecv(WPARAM wParam, LPARAM lParam) {
	LPCTSTR IpszStr = (LPCTSTR)lParam;

	m_list_msg.InsertString(-1, IpszStr);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	return 0;
}


//�������� -> Ŭ���̾�Ʈ�� ���� Count ���� ����
afx_msg LRESULT CsocClientDlg::OnClientCountRecv(WPARAM wParam, LPARAM lParam) {
	
	int Count = (int)lParam;
	
	//m_StartCount = Count;

	m_Client_Count.Format(_T("%d"), Count);
	UpdateData(FALSE);


	return 0;
}


void CsocClientDlg::OnClickedButtonCon()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�

	UpdateData(TRUE);
	if (m_edit_ip == "")AfxMessageBox(_T("����IP�� �Է����ּ���."));
	else {
		if (m_ClientSocket.Connect(m_edit_ip, PORT) == FALSE) {
			AfxMessageBox(_T("==connect ����, �ּ��ʱ�ȭ=="));
			PostQuitMessage(0);
		}
	}
}




//���� ���۹�ư Ŭ���̾�Ʈ-> ������
void CsocClientDlg::OnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//AfxMessageBox(_T("���ӽ����̴�"));
	Invalidate();

	m_start = TRUE;
	m_ClickCheck = FALSE;
	//CString str;
	UpdateData(TRUE);

//	m_ClickCheck = FALSE;
	
	GameStart* temp = new GameStart;
	
	temp->id = 200;
	temp->size = sizeof(GameStart);
	temp->g_start.b_start = m_start;
	temp->g_start.b_clickCheck = m_ClickCheck;
	
	//Ŭ���̾�Ʈ->������
	m_ClientSocket.Send((char *)temp, sizeof(GameStart));

	delete temp;
	UpdateData(FALSE);

	
}


//������ư
void CsocClientDlg::OnClickedButtonRock()
{
	UpdateData(TRUE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	if (m_start == TRUE ) {
		m_ClickCheck == TRUE;
		
		m_choice = 1;
		m_choice_msg.Format(_T("����� ������ �����"));
		UpdateData(FALSE);
	
		OnImagePrint();
		
		SendMyRock* temp = new SendMyRock;
		temp->id = 401;
		temp->size = sizeof(SendMyRock);
		temp->SendOutRock.InRock = m_choice;
		/*��Ʈ��*/
		temp->SendOutRock.PLAYER1 = m_PlayerPortNum;
		temp->SendOutRock.PLAYER2 = m_Player2PortNum;

		m_ClientSocket.Send((char *)temp, sizeof(SendMyRock));
		delete temp;
		//UpdateData(FALSE);
		
		m_start = FALSE;
	}
	else if(m_start == FALSE){
		m_choice_msg.Format(_T("���۹�ư�� ������1"));
		UpdateData(FALSE);
	}
}


//������ư
void CsocClientDlg::OnClickedButtonScissors()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_start == TRUE) {
		m_choice = 2;
		m_choice_msg.Format(_T("����� ������ �����"));
		UpdateData(FALSE);
		OnImagePrint();
		SendMyScissors* temp = new SendMyScissors;
		temp->id = 402;
		temp->size = sizeof(SendMyScissors);
		temp->SendOutScissors.InScissors = m_choice;
		/*��Ʈ��*/
		temp->SendOutScissors.PLAYER1 = m_PlayerPortNum;
		temp->SendOutScissors.PLAYER2 = m_Player2PortNum;

		m_ClientSocket.Send((char *)temp, sizeof(SendMyScissors));
		delete temp;


		m_start = FALSE;
	}
	else if (m_start == FALSE) {
		m_choice_msg.Format(_T("���۹�ư�� ������2"));
		UpdateData(FALSE);
	}
}




//����ư
void CsocClientDlg::OnClickedButtonPaper()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_start == TRUE) {
		m_choice = 3;
		m_choice_msg.Format(_T("����� ���� �����"));
		UpdateData(FALSE);
		OnImagePrint();

		SendMyPaper* temp = new SendMyPaper;
		temp->id = 403;
		temp->size = sizeof(SendMyScissors);
		temp->SendOutPaper.InPaper = m_choice;
		/*��Ʈ��*/
		temp->SendOutPaper.PLAYER1 = m_PlayerPortNum;
		temp->SendOutPaper.PLAYER2 = m_Player2PortNum;

		m_ClientSocket.Send((char *)temp, sizeof(SendMyPaper));
		delete temp;

		m_start = FALSE;
	}
	else if (m_start == FALSE) {
		m_choice_msg.Format(_T("���۹�ư�� ������3"));
		UpdateData(FALSE);
	}
}






/*�̹������ �Լ�*/
void CsocClientDlg::OnImagePrint() {
	srand(time(NULL));
	CImage img;
	CClientDC dc(this);

	
	if (m_choice == 1) {
		img.Load(_T("1.jpg"));
		img.BitBlt(dc.m_hDC, 30, 70);

	}
	else if (m_choice == 2) {
		img.Load(_T("2.jpg"));
		img.BitBlt(dc.m_hDC, 30, 70);
	}
	else if (m_choice == 3) {
		img.Load(_T("3.jpg"));
		img.BitBlt(dc.m_hDC, 30, 70);
	}

	
	//�̹��� �ı��ϱ�
	//img.Destroy();
	//������ ���ΰ�ħ
}

void CsocClientDlg::OnImagePrint2() {
	srand(time(NULL));
	CImage img2;
	CClientDC dc2(this);

	if (m_Swich2 == TRUE) {

		if (m_EnemyChoice1 == 1) {
			img2.Load(_T("1.jpg"));
			img2.BitBlt(dc2.m_hDC, 410, 70);
		}
		else if (m_EnemyChoice1 == 2) {
			img2.Load(_T("2.jpg"));
			img2.BitBlt(dc2.m_hDC, 410, 70);
		}
		else if (m_EnemyChoice1 == 3) {
			img2.Load(_T("3.jpg"));
			img2.BitBlt(dc2.m_hDC, 390, 70);
		}

	}
	else if (m_Swich1 == TRUE) {

		if (m_EnemyChoice2 == 1) {
			img2.Load(_T("1.jpg"));
			img2.BitBlt(dc2.m_hDC, 410, 70);
		}
		else if (m_EnemyChoice2 == 2) {
			img2.Load(_T("2.jpg"));
			img2.BitBlt(dc2.m_hDC, 410, 70);
		}
		else if (m_EnemyChoice2 == 3) {
			img2.Load(_T("3.jpg"));
			img2.BitBlt(dc2.m_hDC, 410, 70);
		}

	}


}



afx_msg LRESULT CsocClientDlg::OnPlayerPortNumRecv(WPARAM wParam, LPARAM lParam)
{
	 MyPortNum* Player = (MyPortNum*)lParam;
	
	 if (m_start == TRUE && m_PlayerPortNum == 0) {
			 m_PlayerPortNum = Player->PlayerPortNum;
			
			 if (m_PlayerPortNum != 0 && Player->PLAYER == 1) {
				 m_MyPortNum_Msg.Format(_T("����� Player1 ��Ʈ��ȣ : %d"), m_PlayerPortNum);
				 UpdateData(FALSE);

			 }
			 else if(Player->PLAYER == 2){
				 m_Player2PortNum = Player->PlayerPortNum;

			m_MyPortNum_Msg.Format(_T("����� Player2��Ʈ��ȣ : %d"), m_Player2PortNum);
			 UpdateData(FALSE);
		 }
		
	 }

	return 0;
}


afx_msg LRESULT CsocClientDlg::OnEnemyValueRecv(WPARAM wParam, LPARAM lParam) {
	
	MyEnemy1Value* Enemy1Value = (MyEnemy1Value *)lParam;
	MyEnemy2Value* Enemy2Value = (MyEnemy2Value *)lParam;
	//MyEnemyValue* EnemyValue = (MyEnemyValue*)lParam;

	srand(time(NULL));
	CImage E_img2;
	CImage E_img3;
	CClientDC dc2(this);
	CClientDC dc3(this);

	
		//P1 ��Ʈ��ȣ�� ������ ���濡�� �̹����� �Ѹ���
		if (Enemy1Value->Enemy1Port == m_PlayerPortNum) {

			m_EnemyChoice2 = Enemy2Value->Enemy2Value;
			//m_EnemyChoice2 = Enemy1Value->Enemy1Value;

			if (m_EnemyChoice2 == 1) {
				E_img2.Load(_T("1.jpg"));
				E_img2.BitBlt(dc2.m_hDC, 410, 70);
			}
			else if (m_EnemyChoice2 == 2) {
				E_img2.Load(_T("2.jpg"));
				E_img2.BitBlt(dc2.m_hDC, 410, 70);
			}
			else if (m_EnemyChoice2 == 3) {
				E_img2.Load(_T("3.jpg"));
				E_img2.BitBlt(dc2.m_hDC, 410, 70);
			}
			else {
				m_choice_msg.Format(_T("�����̰�����1"));
				UpdateData(FALSE);
			}

		}
		if (Enemy2Value->Enemy2Port == m_Player2PortNum) {

			m_EnemyChoice1 = Enemy1Value->Enemy1Value;

			if (m_EnemyChoice1 == 1) {
				E_img3.Load(_T("1.jpg"));
				E_img3.BitBlt(dc3.m_hDC, 410, 70);
			}
			else if (m_EnemyChoice1 == 2) {
				E_img3.Load(_T("2.jpg"));
				E_img3.BitBlt(dc3.m_hDC, 410, 70);
			}
			else if (m_EnemyChoice1 == 3) {
				E_img3.Load(_T("3.jpg"));
				E_img3.BitBlt(dc3.m_hDC, 410, 70);
			}
			else {
				m_choice_msg.Format(_T("�����̰�����2"));
				UpdateData(FALSE);
			}

		}
		 
	//�̹��� �ı��ϱ�
	//img2.Destroy();
	//������ ���ΰ�ħ
	

	return 0;
}


/*���� ����� ���*/
afx_msg LRESULT CsocClientDlg::OnPlayResultRecv(WPARAM wParam, LPARAM lParam) {
	MyResult* result = (MyResult*)lParam;
	
	if (m_Swich1 == m_Swich2) {

		if (result->Playdraw == 5) {
			m_choice_msg.Format(_T("���º��̴�."));
			UpdateData(FALSE);
		}
		if (result->Player1Result == 1) {
			m_choice_msg.Format(_T("Player1�� �¸��ߴ�"));
			UpdateData(FALSE);
		}
		else if (result->Player1Result == 2) {
			m_choice_msg.Format(_T("Player1 �й��ߴ�"));
			UpdateData(FALSE);
		}
		if (result->Player2Result == 3) {
			m_choice_msg.Format(_T("Player2 �¸��ߴ�"));
			UpdateData(FALSE);
		}
		else if (result->Player2Result == 3) {
			m_choice_msg.Format(_T("Player2 �й��ߴ�"));
			UpdateData(FALSE);

		}
		m_Swich1 = FALSE;
		m_Swich2 = FALSE;
	}
	return 0;
}





void CsocClientDlg::OnEnChangeEditSend()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
void CsocClientDlg::OnEnChangeEditMyportnum()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
//IP����â
void CsocClientDlg::OnEnChangeEditIp()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

/*************************************************************************************/
/******************************************************************/

//ī��Ʈ �����̴�
void CsocClientDlg::OnChangeEditCount()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


//���̽� ���� �޼���
void CsocClientDlg::OnChangeEditChoice()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


/******************************************************************/
/*
afx_msg LRESULT CsocClientDlg::OnEnemy2ValueRecv(WPARAM wParam, LPARAM lParam) {
	
	MyEnemy1Value* Enemy1Value = (MyEnemy1Value *)lParam;
	MyEnemy2Value* Enemy2Value = (MyEnemy2Value *)lParam;

	srand(time(NULL));
	
	CImage E_img2;
	CClientDC dc3(this);

	if (Enemy2Value->Enemy2Port == m_Player2PortNum) {

		//Enemy1Value->Enemy1Value= m_EnemyChoice2;

		m_EnemyChoice1 = Enemy1Value->Enemy1Value;

		if (m_EnemyChoice1 == 1) {
			E_img2.Load(_T("1.jpg"));
			E_img2.BitBlt(dc3.m_hDC, 390, 70);
		}
		else if (m_EnemyChoice1 == 2) {
			E_img2.Load(_T("2.jpg"));
			E_img2.BitBlt(dc3.m_hDC, 390, 70);
		}
		else if (m_EnemyChoice1 == 3) {
			E_img2.Load(_T("3.jpg"));
			E_img2.BitBlt(dc3.m_hDC, 390, 70);
		}
		else {
			m_choice_msg.Format(_T("�ù߿���2"));
			UpdateData(FALSE);
		}

	}
	return 0;
}
*/
