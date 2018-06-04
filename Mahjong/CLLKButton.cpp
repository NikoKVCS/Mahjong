
#include "stdafx.h"
#include "CLLKButton.h"
#include "ctime"

//初始化全局变量
CLLKButton* CLLKButton::firstBtn = NULL;
CLLKButton* CLLKButton::secondBtn = NULL;
CPoint CLLKButton::conner1(-1, -1);
CPoint CLLKButton::conner2(-1, -1);
CDialogMain* CLLKButton::game = NULL;


IMPLEMENT_DYNAMIC(CLLKButton, CButton)

CLLKButton::CLLKButton()
	: ID(0)
	, location(0)
{

}

// 析构
CLLKButton::~CLLKButton()
{
}


BEGIN_MESSAGE_MAP(CLLKButton, CButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// 有参构造
CLLKButton::CLLKButton(int type, CPoint point)
{
	location = point;
	ID = type;

}


// 一条直线消子
bool CLLKButton::LinkInLine(CPoint p1, CPoint p2)
{
	return false;
}

// 两条直线消子
bool CLLKButton::OneCornerLink(CPoint p1, CPoint p2)
{
	return false;
}

// 三条直线消子
bool CLLKButton::TwoCornerLink(CPoint p1, CPoint p2)
{
	return false;
}

// 点击按钮响应函数
void CLLKButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	
}


