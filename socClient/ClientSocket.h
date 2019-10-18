#pragma once
#define WM_CLIENT_RECV WM_USER+1
#define WM_Count_RECV WM_USER+2
#define WM_PlayerPort_RECV WM_USER+3
#define WM_Result_RECV WM_USER+4
#define WM_EnemyValue_RECV WM_USER+5
#define WM_Enemy2Value_RECV WM_USER+6

// CClientSocket 명령 대상입니다.

/***************메세지구조체****************/
struct MyMessage {
	//LPCTSTR data;
	TCHAR strBuffer[1024];
};
struct ReceivMessages {
	int id;
	int size;
	MyMessage msg;
};

/****************Start구조체********************/
struct MyStart
{
	bool b_start;
	bool b_clickCheck;
	UINT portNum;
};
struct GameStart
{
	int id;
	int size;
	MyStart g_start;

};
/****************Count구조체********************/
struct MyCount
{
	int OnCount;
};
struct SendCount
{
	int id;
	int size;
	MyCount SendOnCount;
};



/********************바위 구조체*******************/
struct MyRock {
	int InRock;
	UINT PLAYER1;
	UINT PLAYER2;
};
struct SendMyRock {
	int id;
	int size;
	MyRock SendOutRock;
};

/********************가위 구조체*******************/
struct MyScissors {
	int InScissors;
	UINT PLAYER1;
	UINT PLAYER2;
};
struct SendMyScissors {
	int id;
	int size;
	MyScissors SendOutScissors;
};
/********************보 구조체*******************/
struct MyPaper {
	int InPaper;
	UINT PLAYER1;
	UINT PLAYER2;
};
struct SendMyPaper {
	int id;
	int size;
	MyPaper SendOutPaper;
};


/********포트번호클라이언트에게 보내기**********/
struct MyPortNum
{
	UINT PlayerPortNum;
	int PLAYER;
};
struct PortNum {
	int id;
	int size;
	MyPortNum SendPlayerPortNum;

};


struct MyEnemy1Value
{
	int Enemy1Value;
	UINT Enemy1Port;
};
struct SendMyEnemy1Value
{
	int id;
	int size;
	MyEnemy1Value Enemy1Value;
};


struct MyEnemy2Value
{
	int Enemy2Value;
	UINT Enemy2Port;
};
struct SendMyEnemy2Value
{
	int id;
	int size;
	MyEnemy2Value Enemy2Value;
};


/*클라이언트에서 보내는 상대방 value*/
/*
struct MyEnemyValue
{
	int Enemy1Value;
	UINT Enemy1Port;
	int Enemy2Value;
	UINT Enemy2Port;
};
struct SendMyEnemyValue
{
	int id;
	int size;
	MyEnemyValue EnemyValue;

};
*/

/********최종결과값 서버에서보낸거 받기**********/
struct MyResult
{
	int Player1Result;
	int Player2Result;
	int Playdraw;
	
};
struct SendMyResult
{
	int id;
	int size;
	MyResult SendOutResult;
};



class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	//윈도우 아이디를 받는다 핸들함수
	void SetWnd(HWND m_hWnd);
	//서버통신을 받을시 의 처리함수 
	virtual void OnReceive(int nErrorCode);
	//소켓해제시의 처리함수 
	virtual void OnClose(int nErrorCode);
	HWND m_hWnd;
};


