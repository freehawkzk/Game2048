
// Game2048Dlg.h : 头文件
//

#pragma once


// CGame2048Dlg 对话框
class CGame2048Dlg : public CDialogEx
{
// 构造
public:
	CGame2048Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME2048_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void DrawGameRect();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void ResetGameMap();//初始化棋盘数据
	void AddABlock();//向棋盘中添加一个方块
	void AddBlocks(int nCount = 2);//一次添加多个方块，默认添加2个
	void DrawBlocks();//根据棋盘数据绘制方块
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
