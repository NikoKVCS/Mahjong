// CDialogMain.cpp: 实现文件
//

#include "stdafx.h"
#include "Mahjong.h"
#include "CDialogMain.h"
#include "afxdialogex.h"
#include "CLLKButton.h"




// CDialogMain 对话框

IMPLEMENT_DYNAMIC(CDialogMain, CDialogEx)

CDialogMain::CDialogMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDialogMain::~CDialogMain()
{
}

void CDialogMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogMain, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogMain::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDialogMain 消息处理程序


void CDialogMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CRect rctClient;
	GetClientRect(rctClient);
	CDC dcMem;
	dcMem.CreateCompatibleDC(GetDC());
	CBitmap m_bmp;
	m_bmp.LoadBitmap(IDC_BMP_BG2);
	BITMAP bitmap;
	m_bmp.GetBitmap(&bitmap);
	CBitmap   *pbmpOld = dcMem.SelectObject(&m_bmp);
	GetDC()->StretchBlt(0, 0, rctClient.Width(), rctClient.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


	CWindowDC dc2(this);
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	dc2.SelectObject(pen);

	//画出路径
	if (CLLKButton::firstBtn != NULL && CLLKButton::secondBtn != NULL)
	{
		//设置计时器，0.2秒后擦除路径线条
		SetTimer(1, 200, 0);
		pt1.x = CLLKButton::firstBtn->location.y * 50 + 45;
		pt1.y = CLLKButton::firstBtn->location.x * 50 + 70;
		pt2.x = CLLKButton::secondBtn->location.y * 50 + 45;
		pt2.y = CLLKButton::secondBtn->location.x * 50 + 70;
		pt3.x = CLLKButton::conner1.y * 50 + 45;
		pt3.y = CLLKButton::conner1.x * 50 + 70;
		pt4.x = CLLKButton::conner2.y * 50 + 45;
		pt4.y = CLLKButton::conner2.x * 50 + 70;

		//无拐点
		if (CLLKButton::conner1.x == -1)
		{
			dc2.MoveTo(pt1);
			dc2.LineTo(pt2);
		}
		//一个拐点
		else if (CLLKButton::conner2.x == -1)
		{
			dc2.MoveTo(pt1);
			dc2.LineTo(pt3);
			dc2.MoveTo(pt3);
			dc2.LineTo(pt2);
		}
		//两个拐点
		else
		{
			dc2.MoveTo(pt1);
			dc2.LineTo(pt3);
			dc2.MoveTo(pt3);
			dc2.LineTo(pt4);
			dc2.MoveTo(pt4);
			dc2.LineTo(pt2);
		}
	}
}



// 初始化地图
void CDialogMain::InitMap()
{
	for (int i = 0; i < MAX_X; i++) // 初始化map数组
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			map[i][j] = 0;
		}
	}

	//随机数种子
	srand((unsigned int)time(NULL));

	for (int i = 1; i < MAX_X - 1; i++)
	{
		for (int j = 1; j < MAX_Y - 1; j = j + 2)
		{
			int type = rand() % m_typeNum + 1;// 随机产生一个的图片种类编号
			map[i][j] = type;
			map[i][j + 1] = type; // 保证同种图片连续出现两次
		}
	}
	int k = 0;
	while (k < 100) // 随机选中两个位置交换100次
	{
		int x1 = 0, y1 = 0;
		int x2 = 0, y2 = 0;
		while (x1 == x2 && y1 == y2) // 确保两个位置不同
		{
			x1 = rand() % (MAX_X - 2) + 1;
			y1 = rand() % (MAX_Y - 2) + 1;

			x2 = rand() % (MAX_X - 2) + 1;
			y2 = rand() % (MAX_Y - 2) + 1;
		}
		int temp = map[x1][y1];
		map[x1][y1] = map[x2][y2];
		map[x2][y2] = temp;
		k++;
	}
}


// 显示地图
void CDialogMain::ShowMap()
{
	InitMap();

	int i, j;
	CPoint p; // 按钮位置
	CString str = _T("");
	//清除原有按钮
	for (i = 0; i<m_btnGroup.GetSize(); i++)
		delete (CLLKButton *)m_btnGroup.GetAt(i);
	m_btnGroup.RemoveAll();

	//添加新按钮
	for (i = 1; i <= MAX_X - 2; i++)
	{
		for (j = 1; j <= MAX_Y - 2; j++)
		{
			p.x = i;
			p.y = j;
			//arr[map[i][j] - 1]++;
			//将按钮放入m_btnGroup指针数组中
			m_btnGroup.Add(new CLLKButton(map[i][j], p));

		}
	}

	//显示按钮
	for (i = 0; i<(MAX_X - 2)*(MAX_Y - 2); i++)
	{
		CLLKButton *btn = (CLLKButton *)m_btnGroup.GetAt(i);
		if (btn->ID > 0)
		{
			str.Format(_T("res\\c%d.bmp"), btn->ID);

			CImage image;
			image.Load(str);

			btn->Create(str, WS_CHILD | BS_BITMAP | WS_VISIBLE,
				CRect(50 + (i % (MAX_Y - 2)) * 50, 90 + (i / (MAX_Y - 2)) * 50,
					100 + (i % (MAX_Y - 2)) * 50, 140 + (i / (MAX_Y - 2)) * 50), this,
				IDC_BLOCK + i);
			btn->SetBitmap(image);
			btn->ShowWindow(SW_SHOW);
		}
	}


}


void CDialogMain::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 开局啦
	CLLKButton::game = this;
	ShowMap();
}


void CDialogMain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == 1) // 消除连线
	{
		{
			CWindowDC dc2(this);
			//用背景色将路径再画一次  
			CPen pen(PS_SOLID, 5, RGB(200, 191, 231));
			dc2.SelectObject(pen);
			//无拐点
			if (CLLKButton::conner1.x == -1)
			{
				dc2.MoveTo(pt1);
				dc2.LineTo(pt2);
			}
			//一个拐点
			else if (CLLKButton::conner2.x == -1)
			{
				dc2.MoveTo(pt1);
				dc2.LineTo(pt3);
				dc2.MoveTo(pt3);
				dc2.LineTo(pt2);
			}
			//两个拐点
			else
			{
				dc2.MoveTo(pt1);
				dc2.LineTo(pt3);
				dc2.MoveTo(pt3);
				dc2.LineTo(pt4);
				dc2.MoveTo(pt4);
				dc2.LineTo(pt2);
			}
		}
		KillTimer(nIDEvent);
	}


	CDialogEx::OnTimer(nIDEvent);
}



// 判断是否通关
bool CDialogMain::IsFinished()
{
	bool b = true;
	for (int i = 1; i < MAX_X - 1; i++)
	{
		for (int j = 1; j < MAX_Y - 1; j++)
		{
			if (map[i][j] != 0)
			{
				b = false;
				break;
			}
		}
	}
	return b;
}
