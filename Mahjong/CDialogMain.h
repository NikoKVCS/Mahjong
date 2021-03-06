#pragma once



#define MAX_X 8 
#define MAX_Y 14 
#define m_typeNum 8

// CDialogMain 对话框

class CDialogMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMain)

public:
	CDialogMain(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogMain();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();


	int map[MAX_X][MAX_Y];

	bool IsFinished();
private:
private:
	CPtrArray m_btnGroup;

	CPoint pt1;
	CPoint pt2;
	CPoint pt3;
	CPoint pt4;

	void ShowMap();
	void InitMap();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
