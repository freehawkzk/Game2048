
// Game2048Dlg.h : ͷ�ļ�
//

#pragma once


// CGame2048Dlg �Ի���
class CGame2048Dlg : public CDialogEx
{
// ����
public:
	CGame2048Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME2048_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void DrawGameRect();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void ResetGameMap();//��ʼ����������
	void AddABlock();//�����������һ������
	void AddBlocks(int nCount = 2);//һ����Ӷ�����飬Ĭ�����2��
	void DrawBlocks();//�����������ݻ��Ʒ���
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CCriticalSection m_lock;

	void MoveBlocks(int nDir);
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockUp();
	void MoveBlockDown();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	int m_nCurrentLevel;
	int m_nCurrentScore;
	bool CheckGameOver();
	int m_nFreePos;

	afx_msg LRESULT OnGameOver(WPARAM, LPARAM);
	afx_msg LRESULT OnMoveBlocks(WPARAM, LPARAM);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
