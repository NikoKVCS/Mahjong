
#include "stdafx.h"
#include "CLLKButton.h"
#include "ctime"

//��ʼ��ȫ�ֱ���
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

// ����
CLLKButton::~CLLKButton()
{
}


BEGIN_MESSAGE_MAP(CLLKButton, CButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// �вι���
CLLKButton::CLLKButton(int type, CPoint point)
{
	location = point;
	ID = type;

}


// һ��ֱ������
bool CLLKButton::LinkInLine(CPoint p1, CPoint p2)
{
	return false;
}

// ����ֱ������
bool CLLKButton::OneCornerLink(CPoint p1, CPoint p2)
{
	return false;
}

// ����ֱ������
bool CLLKButton::TwoCornerLink(CPoint p1, CPoint p2)
{
	return false;
}

// �����ť��Ӧ����
void CLLKButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	
}


