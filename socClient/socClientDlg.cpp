
// socClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "socClient.h"
#include "socClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define PORT 9999
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CsocClientDlg 대화 상자



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
	//IDC_BUTTON_SEND을 함수 OnClickedButtonSend에 담아준다 클라이언트-> 서버로
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CsocClientDlg::OnClickedButtonSend)
	
	/*****************************************************************/
	//서버->클라이언트
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


// CsocClientDlg 메시지 처리기

BOOL CsocClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	//윈도우 아이디 주소 값의 초기화 작업 
	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	/*
	if (m_ClientSocket.Connect(_T("192.168.0.10"),PORT) == FALSE){
		
		AfxMessageBox(_T("==connect 에러, 주소초기화 에러=="));
		PostQuitMessage(0);
		return FALSE;
	}
	*/
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CsocClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CsocClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsocClientDlg::OnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	UpdateData(true);
	
  //str 담아준다
	m_edit_send.GetWindowTextW(str);

	/*구조체에 맞게 설정을 해준다 */
	ReceivMessages* temp = new ReceivMessages;
	temp->id = 100;
	temp->size = sizeof(MyMessage);
	//카피구조체에 있는 
	_tcscpy(temp->msg.strBuffer, str);


	m_ClientSocket.Send((char *)temp, sizeof(MyMessage));
	//실제로 서버에 보내주는에 
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


//서버에서 -> 클라이언트로 보낸 Count 숫자 감속
afx_msg LRESULT CsocClientDlg::OnClientCountRecv(WPARAM wParam, LPARAM lParam) {
	
	int Count = (int)lParam;
	
	//m_StartCount = Count;

	m_Client_Count.Format(_T("%d"), Count);
	UpdateData(FALSE);


	return 0;
}


void CsocClientDlg::OnClickedButtonCon()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다

	UpdateData(TRUE);
	if (m_edit_ip == "")AfxMessageBox(_T("접속IP를 입력해주세요."));
	else {
		if (m_ClientSocket.Connect(m_edit_ip, PORT) == FALSE) {
			AfxMessageBox(_T("==connect 에러, 주소초기화=="));
			PostQuitMessage(0);
		}
	}
}




//게임 시작버튼 클라이언트-> 서버로
void CsocClientDlg::OnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("게임시작이다"));
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
	
	//클라이언트->서버로
	m_ClientSocket.Send((char *)temp, sizeof(GameStart));

	delete temp;
	UpdateData(FALSE);

	
}


//바위버튼
void CsocClientDlg::OnClickedButtonRock()
{
	UpdateData(TRUE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (m_start == TRUE ) {
		m_ClickCheck == TRUE;
		
		m_choice = 1;
		m_choice_msg.Format(_T("당신은 바위를 골랐다"));
		UpdateData(FALSE);
	
		OnImagePrint();
		
		SendMyRock* temp = new SendMyRock;
		temp->id = 401;
		temp->size = sizeof(SendMyRock);
		temp->SendOutRock.InRock = m_choice;
		/*포트넘*/
		temp->SendOutRock.PLAYER1 = m_PlayerPortNum;
		temp->SendOutRock.PLAYER2 = m_Player2PortNum;

		m_ClientSocket.Send((char *)temp, sizeof(SendMyRock));
		delete temp;
		//UpdateData(FALSE);
		
		m_start = FALSE;
	}
	else if(m_start == FALSE){
		m_choice_msg.Format(_T("시작버튼을 눌러라1"));
		UpdateData(FALSE);
	}
}


//가위버튼
void CsocClientDlg::OnClickedButtonScissors()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_start == TRUE) {
		m_choice = 2;
		m_choice_msg.Format(_T("당신은 가위를 골랐다"));
		UpdateData(FALSE);
		OnImagePrint();
		SendMyScissors* temp = new SendMyScissors;
		temp->id = 402;
		temp->size = sizeof(SendMyScissors);
		temp->SendOutScissors.InScissors = m_choice;
		/*포트넘*/
		temp->SendOutScissors.PLAYER1 = m_PlayerPortNum;
		temp->SendOutScissors.PLAYER2 = m_Player2PortNum;

		m_ClientSocket.Send((char *)temp, sizeof(SendMyScissors));
		delete temp;


		m_start = FALSE;
	}
	else if (m_start == FALSE) {
		m_choice_msg.Format(_T("시작버튼을 눌러라2"));
		UpdateData(FALSE);
	}
}




//보버튼
void CsocClientDlg::OnClickedButtonPaper()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_start == TRUE) {
		m_choice = 3;
		m_choice_msg.Format(_T("당신은 보를 골랐다"));
		UpdateData(FALSE);
		OnImagePrint();

		SendMyPaper* temp = new SendMyPaper;
		temp->id = 403;
		temp->size = sizeof(SendMyScissors);
		temp->SendOutPaper.InPaper = m_choice;
		/*포트넘*/
		temp->SendOutPaper.PLAYER1 = m_PlayerPortNum;
		temp->SendOutPaper.PLAYER2 = m_Player2PortNum;

		m_ClientSocket.Send((char *)temp, sizeof(SendMyPaper));
		delete temp;

		m_start = FALSE;
	}
	else if (m_start == FALSE) {
		m_choice_msg.Format(_T("시작버튼을 눌러라3"));
		UpdateData(FALSE);
	}
}






/*이미지출력 함수*/
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

	
	//이미지 파괴하기
	//img.Destroy();
	//페이지 새로고침
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
				 m_MyPortNum_Msg.Format(_T("당신은 Player1 포트번호 : %d"), m_PlayerPortNum);
				 UpdateData(FALSE);

			 }
			 else if(Player->PLAYER == 2){
				 m_Player2PortNum = Player->PlayerPortNum;

			m_MyPortNum_Msg.Format(_T("당신은 Player2포트번호 : %d"), m_Player2PortNum);
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

	
		//P1 포트번호가 같으면 상대방에게 이미지를 뿌린다
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
				m_choice_msg.Format(_T("상대방이고르는중1"));
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
				m_choice_msg.Format(_T("상대방이고르는중2"));
				UpdateData(FALSE);
			}

		}
		 
	//이미지 파괴하기
	//img2.Destroy();
	//페이지 새로고침
	

	return 0;
}


/*최종 결과값 출력*/
afx_msg LRESULT CsocClientDlg::OnPlayResultRecv(WPARAM wParam, LPARAM lParam) {
	MyResult* result = (MyResult*)lParam;
	
	if (m_Swich1 == m_Swich2) {

		if (result->Playdraw == 5) {
			m_choice_msg.Format(_T("무승부이다."));
			UpdateData(FALSE);
		}
		if (result->Player1Result == 1) {
			m_choice_msg.Format(_T("Player1이 승리했다"));
			UpdateData(FALSE);
		}
		else if (result->Player1Result == 2) {
			m_choice_msg.Format(_T("Player1 패배했다"));
			UpdateData(FALSE);
		}
		if (result->Player2Result == 3) {
			m_choice_msg.Format(_T("Player2 승리했다"));
			UpdateData(FALSE);
		}
		else if (result->Player2Result == 3) {
			m_choice_msg.Format(_T("Player2 패배했다"));
			UpdateData(FALSE);

		}
		m_Swich1 = FALSE;
		m_Swich2 = FALSE;
	}
	return 0;
}





void CsocClientDlg::OnEnChangeEditSend()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CsocClientDlg::OnEnChangeEditMyportnum()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
//IP적는창
void CsocClientDlg::OnEnChangeEditIp()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

/*************************************************************************************/
/******************************************************************/

//카운트 움직이는
void CsocClientDlg::OnChangeEditCount()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//초이스 상태 메세지
void CsocClientDlg::OnChangeEditChoice()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			m_choice_msg.Format(_T("시발에러2"));
			UpdateData(FALSE);
		}

	}
	return 0;
}
*/
