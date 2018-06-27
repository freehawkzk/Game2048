
// Game2048Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Game2048.h"
#include "Game2048Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGame2048Dlg �Ի���



CGame2048Dlg::CGame2048Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME2048_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurrentLevel = 0;
	m_nCurrentScore = 0;
	m_nFreePos = 0;
}

void CGame2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGame2048Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON2, &CGame2048Dlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CGame2048Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGame2048Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CGame2048Dlg::OnBnClickedButton1)
	ON_MESSAGE(WM_GAME_OVER,&CGame2048Dlg::OnGameOver)
	ON_MESSAGE(WM_MOVE_BLOCKS,&CGame2048Dlg::OnMoveBlocks)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CGame2048Dlg ��Ϣ�������

BOOL CGame2048Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ResetGameMap();
	SetTimer(0, 5000, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGame2048Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGame2048Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		DrawGameRect();
		DrawBlocks();
		TCHAR buf[32] = { 0 };
		wsprintf(buf, L"%d", m_nCurrentScore);
		GetDlgItem(IDC_CURRENT_SCORE)->SetWindowTextW(buf);
		CheckGameOver();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGame2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGame2048Dlg::DrawGameRect()
{
	CDC* pDC = GetDC();
	Gdiplus::Graphics g(pDC->m_hDC);
	Gdiplus::Pen pen(g_colorBordLine,g_fBordLineWidth);
	RECT rt;
	GetClientRect(&rt);
	float fGameAreaWidth = (rt.right - rt.left)*0.8f;
	float fGameAreaHeight = rt.bottom - rt.top;
	Gdiplus::Rect gameRect(g_fBordLineWidth / 2.0, g_fBordLineWidth / 2.0, fGameAreaWidth - g_fBordLineWidth, fGameAreaHeight - g_fBordLineWidth);
	Gdiplus::SolidBrush brush(g_colorGameBkg);
	g.FillRectangle(&brush, gameRect);
	g.DrawRectangle(&pen, gameRect);
	ReleaseDC(pDC);
}

BOOL CGame2048Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}

void CGame2048Dlg::ResetGameMap()
{
	m_lock.Lock();
	if (g_vvData.size() > 0)
	{
		for each ( auto  v in g_vvData)
		{
			v.clear();
		}
		g_vvData.clear();
	}

	for (int i = 0; i < g_nBlockNumY; i++)
	{
		g_vvData.push_back(std::vector<int>(g_nBlockNumX, 0));
	}
	m_lock.Unlock();

	m_nCurrentScore = 0;
}

void CGame2048Dlg::AddABlock()//�����������һ������
{
	int nX = 0; 
	int nY = 0;
	do 
	{
		nX = rand() % g_nBlockNumY;
		nY = rand() % g_nBlockNumX;
	} while (g_vvData[nX][nY] != 0);
	
	m_lock.Lock();
	g_vvData[nX][nY] = 2 * (rand() % 2) + 2;
	m_lock.Unlock();
}

void CGame2048Dlg::AddBlocks(int nCount /*= 2*/)//һ����Ӷ�����飬Ĭ�����2��
{
	bool hr = CheckGameOver();
	if (!hr)
	{
		int nCount = 0;
		if (m_nFreePos >=2)
		{
			for (int i = 0; i < 2; i++)
			{
				AddABlock();
			}
		}
		else if (m_nFreePos == 1)
		{
			AddABlock();
		}
	}
	else
	{
		KillTimer(0);
	}
}

void CGame2048Dlg::DrawBlocks()
{
	CDC* pDC = GetDC();
	Gdiplus::Graphics g(pDC->m_hDC);


	RECT rt;
	GetClientRect(&rt);
	float fWidth = (rt.right - rt.left) * 0.8f;
	float fHeight = rt.bottom - rt.top;

	float fBlockWidth = (fWidth - 2 * g_fBordLineWidth - (g_nBlockNumX + 1)*g_fGapWidth) / g_nBlockNumX;
	float fBlockHeight = (fHeight - 2 * g_fBordLineWidth - (g_nBlockNumY + 1)*g_fGapWidth) / g_nBlockNumY;


	Gdiplus::FontFamily fontFamily(L"����");
	Gdiplus::Font myFont(&fontFamily, 40, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPoint); //�ڶ����������С
	Gdiplus::StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	for (int i = 0; i < g_nBlockNumY; i++)
	{
		for ( int j = 0; j < g_nBlockNumX; j++)
		{

			if (g_vvData[i][j] != 0)
			{
				Gdiplus::SolidBrush b(g_colorMap[g_vvData[i][j]]);
				Gdiplus::Rect blockRt(g_fBordLineWidth + g_fGapWidth*(j + 1) + j*fBlockWidth, g_fBordLineWidth + g_fGapWidth*(i + 1) + i*fBlockHeight, fBlockWidth, fBlockHeight);
				g.FillRectangle(&b, blockRt);
				Gdiplus::SolidBrush textBrush(g_colorText);
				Gdiplus::PointF pt;
				pt.X = blockRt.GetLeft();
				pt.Y = blockRt.GetTop();
				g.DrawString(g_indexStringMap[g_vvData[i][j]], wcslen(g_indexStringMap[g_vvData[i][j]]), &myFont, pt, &textBrush);
			}
			
		}
	}

	ReleaseDC(pDC);
}

void CGame2048Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MoveBlocks(3);
	Invalidate();
}


void CGame2048Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 0:
		AddBlocks();
		Invalidate();
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CGame2048Dlg::MoveBlocks(int nDir)
{
	switch (nDir)
	{
	case 0:
		MoveBlockLeft();
		break;
	case 1:
		MoveBlockUp();
		break;
	case 2:
		MoveBlockRight();
		break;
	case 3:
		MoveBlockDown();
		break;
	}
	

}

void CGame2048Dlg::MoveBlockLeft()
{
	for (int i = 0; i < g_vvData.size(); i++)
	{
		for (int j = 0; j < g_vvData[i].size(); j++)
		{
			if (g_vvData[i][j] == 0)
			{
				for (int k = j+1; k < g_vvData[i].size();k++)
				{
					if (g_vvData[i][k] != 0)
					{
						g_vvData[i][j] = g_vvData[i][k];
						g_vvData[i][k] = 0;
						break;
					}
				}
			}
		}
		for (int j = g_vvData[i].size()-1; j > 0; j--)
		{
			if (g_vvData[i][j] != 0)
			{
				if (g_vvData[i][j-1] == g_vvData[i][j])
				{
					g_vvData[i][j - 1] *= 2;
					m_nCurrentScore += g_vvData[i][j - 1]*2;
					g_vvData[i][j] = 0;
					for (int m = j; m < g_vvData[i].size()-1; m++)
					{
						g_vvData[i][m] = g_vvData[i][m + 1];
					}
					g_vvData[i][g_vvData[i].size() - 1] = 0;
				}
			}
		}
	}

}
void CGame2048Dlg::MoveBlockRight()
{
	for (int i = 0; i < g_vvData.size(); i++)
	{
		for (int j = g_vvData[i].size() - 1; j >= 0;j--)
		{
			if (g_vvData[i][j] == 0)
			{
				for (int k = j - 1; k >=0; k--)
				{
					if (g_vvData[i][k] != 0)
					{
						g_vvData[i][j] = g_vvData[i][k];
						g_vvData[i][k] = 0;
						break;
					}
				}
			}
		}
		for (int j = 0; j < g_vvData[i].size()-1; j++)
		{
			if (g_vvData[i][j] != 0)
			{
				if (g_vvData[i][j + 1] == g_vvData[i][j])
				{
					g_vvData[i][j + 1] *= 2;

					m_nCurrentScore += g_vvData[i][j + 1]*2;
					g_vvData[i][j] = 0;
					for (int m = j; m > 0; m--)
					{
						g_vvData[i][m] = g_vvData[i][m - 1];
					}
					g_vvData[i][0] = 0;
				}
			}
		}
	}
}
void CGame2048Dlg::MoveBlockUp()
{
	for (int i = 0; i < g_vvData.size(); i++)
	{
		for (int j = 0; j < g_vvData[i].size(); j++)
		{
			if (g_vvData[i][j] == 0)
			{
				for (int m = i; m < g_vvData.size(); m++)
				{
					if (g_vvData[m][j] != 0)
					{
						g_vvData[i][j] = g_vvData[m][j];
						g_vvData[m][j] = 0;
						break;
					}
				}
			}
		}
	}

	for (int j = 0; j < g_vvData[0].size(); j++)
	{
		for (int i = g_vvData.size()-1; i >0; i--)
		{
			if (g_vvData[i][j] != 0 && g_vvData[i-1][j] == g_vvData[i][j])
			{
				g_vvData[i - 1][j] *= 2;
				m_nCurrentScore += g_vvData[i - 1][j]*2;
				for (int k = i; k < g_vvData.size()-1; k++)
				{
					g_vvData[k][j] = g_vvData[k + 1][j];
				}
				g_vvData[g_vvData.size() - 1][j] = 0;
			}
		}
	}
}
void CGame2048Dlg::MoveBlockDown()
{
	for (int i = g_vvData.size()-1; i >= 0 ; i--)
	{
		for (int j = 0; j < g_vvData[i].size(); j++)
		{
			if (g_vvData[i][j] == 0)
			{
				for (int m = i; m >=0; m--)
				{
					if (g_vvData[m][j] != 0)
					{
						g_vvData[i][j] = g_vvData[m][j];
						g_vvData[m][j] = 0;
						break;
					}
				}
			}
		}
	}

	for (int j = 0; j < g_vvData[0].size(); j++)
	{
		for (int i = 0; i < g_vvData.size()-1; i++)
		{
			if (g_vvData[i][j] != 0 && g_vvData[i + 1][j] == g_vvData[i][j])
			{
				g_vvData[i + 1][j] *= 2;
				m_nCurrentScore += g_vvData[i + 1][j]*2;
				for (int k = i; k >0;k--)
				{
					g_vvData[k][j] = g_vvData[k - 1][j];
				}
				g_vvData[0][j] = 0;
			}
		}
	}
}

void CGame2048Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MoveBlocks(0);
	Invalidate();
}


void CGame2048Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MoveBlocks(2);
	Invalidate();
}


void CGame2048Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MoveBlocks(1);
	Invalidate();
}

bool CGame2048Dlg::CheckGameOver()
{
	m_nFreePos = 0;
	for each (auto var in g_vvData)
	{
		for each (auto x in var)
		{
			if (x == 0)
			{
				m_nFreePos++;
			}
			if (x == 2048)
			{
				SendMessage(WM_GAME_OVER, 1, 0);
				return true;
			}
		}

	}
	if (m_nFreePos == 0)
	{
		SendMessage(WM_GAME_OVER, 0, 0);
		return true;
	}


	return false;
}

LRESULT CGame2048Dlg::OnGameOver(WPARAM w, LPARAM)
{
	int nReason = (int)w;
	KillTimer(0);
	switch (nReason)
	{
	case 0:
		
		AfxMessageBox(L"Game Over! You lose!\n There is no place!");
		break;
	case 1:
		AfxMessageBox(L"You win!\n ");
		break;
	}
	
	return 0;
}

LRESULT CGame2048Dlg::OnMoveBlocks(WPARAM w, LPARAM)
{
	int nDir = (int)w;
	MoveBlocks(nDir);
	Invalidate();
	return 0;
}

void CGame2048Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CGame2048Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			break;
		case VK_LEFT:
			SendMessage(WM_MOVE_BLOCKS, 0, 0);
			break;
		case VK_UP:
			SendMessage(WM_MOVE_BLOCKS, 1, 0);
			break;
		case VK_RIGHT:
			SendMessage(WM_MOVE_BLOCKS, 2, 0);
			break;
		case VK_DOWN:
			SendMessage(WM_MOVE_BLOCKS, 3, 0);
			break;
		}
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}
