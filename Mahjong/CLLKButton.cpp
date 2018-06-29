
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
	ID = type;
	location = point;

}


// һ��ֱ������
bool CLLKButton::LinkInLine(CPoint p1, CPoint p2)
{

	conner1.x = conner1.y = -1;
	conner2.x = conner2.y = -1;

	BOOL b = true;
	if (p1.y == p2.y) // ��������ͬһ��
	{
		int min_x = min(p1.x, p2.x);
		int max_x = max(p1.x, p2.x);
		for (int i = min_x + 1; i < max_x; i++)
		{
			if (game->map[i][p1.y] != 0)
			{
				b = false;
			}
		}
	}
	else if (p1.x == p2.x) // ��ͬһ��
	{
		int min_y = min(p1.y, p2.y);
		int max_y = max(p1.y, p2.y);
		for (int i = min_y + 1; i < max_y; i++)
		{
			if (game->map[p1.x][i] != 0)
			{
				b = false;
			}
		}
	}
	else // ����ͬһֱ��
	{
		b = false;
	}
	return b;
}

// ����ֱ������
bool CLLKButton::OneCornerLink(CPoint p1, CPoint p2)
{
	conner1.x = conner1.y = -1;
	conner2.x = conner2.y = -1;

	int min_x = min(p1.x, p2.x);
	int max_x = max(p1.x, p2.x);
	int min_y = min(p1.y, p2.y);
	int max_y = max(p1.y, p2.y);

	// �յ�1
	int x1 = p1.x;
	int y1 = p2.y;
	//�յ�2
	int x2 = p2.x;
	int y2 = p1.y;

	BOOL b = true;
	if (game->map[x1][y1] != 0 && game->map[x2][y2] != 0)
	{
		b = false;
	}
	else
	{
		if (game->map[x1][y1] == 0) // �յ�1λ����ͼƬ
		{
			for (int i = min_x + 1; i < max_x; i++)
			{
				if (game->map[i][y1] != 0)
				{
					b = false;
					break;
				}
			}
			for (int i = min_y + 1; i < max_y; i++)
			{
				if (game->map[x1][i] != 0)
				{
					b = false;
					break;
				}
			}
			if (b)
			{
				conner1.x = x1;
				conner1.y = y1;
				return b;
			}

		}


		if (game->map[x2][y2] == 0) // �յ�2λ����ͼƬ
		{
			b = true;
			for (int i = min_x + 1; i < max_x; i++)
			{
				if (game->map[i][y2] != 0)
				{
					b = false;
					break;
				}
			}
			for (int i = min_y + 1; i < max_y; i++)
			{
				if (game->map[x2][i] != 0)
				{
					b = false;
					break;
				}
			}
			if (b)
			{
				conner1.x = x2;
				conner1.y = y2;
				return b;
			}
		}
	}

	return b;
}

// ����ֱ������
bool CLLKButton::TwoCornerLink(CPoint p1, CPoint p2)
{
	conner1.x = conner1.y = -1;
	conner2.x = conner2.y = -1;

	int min_x = min(p1.x, p2.x);
	int max_x = max(p1.x, p2.x);
	int min_y = min(p1.y, p2.y);
	int max_y = max(p1.y, p2.y);
	bool b;
	for (int i = 0; i < MAX_Y; i++) // ɨ����
	{
		b = true;
		if (game->map[p1.x][i] == 0 && game->map[p2.x][i] == 0) // �����յ�λ����ͼƬ
		{
			for (int j = min_x + 1; j < max_x; j++) // �ж������յ�֮���Ƿ��������
			{
				if (game->map[j][i] != 0)
				{
					b = false;
					break;
				}
			}

			if (b)
			{
				int temp_max = max(p1.y, i);
				int temp_min = min(p1.y, i);
				for (int j = temp_min + 1; j < temp_max; j++) // �ж�p1��������Ӧ�Ĺյ�֮���Ƿ��������
				{
					if (game->map[p1.x][j] != 0)
					{
						b = false;
						break;
					}
				}
			}

			if (b)
			{
				int temp_max = max(p2.y, i);
				int temp_min = min(p2.y, i);
				for (int j = temp_min + 1; j < temp_max; j++) // �ж�p2��������Ӧ�Ĺյ�֮���Ƿ��������
				{
					for (int j = temp_min + 1; j < temp_max; j++)
					{
						if (game->map[p2.x][j] != 0)
						{
							b = false;
							break;
						}
					}
				}
			}
			if (b) // �������·�ߣ�����true
			{
				conner1.x = p1.x;
				conner1.y = i;
				conner2.x = p2.x;
				conner2.y = i;
				return b;
			}
		}

	}// ɨ���н���



	for (int i = 0; i < MAX_X; i++) // ɨ����
	{
		b = true;
		if (game->map[i][p1.y] == 0 && game->map[i][p2.y] == 0) // �����յ�λ����ͼƬ
		{
			for (int j = min_y + 1; j < max_y; j++) // �����յ�֮���Ƿ��������
			{
				if (game->map[i][j] != 0)
				{
					b = false;
					break;
				}
			}

			if (b)
			{
				int temp_max = max(i, p1.x);
				int temp_min = min(i, p1.x);
				for (int j = temp_min + 1; j < temp_max; j++) // �ж�p1��������Ӧ�Ĺյ�֮���Ƿ��������
				{
					if (game->map[j][p1.y] != 0)
					{
						b = false;
						break;
					}
				}
			}

			if (b)
			{
				int temp_max = max(p2.x, i);
				int temp_min = min(p2.x, i);
				for (int j = temp_min + 1; j < temp_max; j++)
				{
					if (game->map[j][p2.y] != 0)
					{
						b = false;
						break;
					}
				}
			}
			if (b) // �������·�ߣ�����true
			{
				conner1.y = p1.y;
				conner1.x = i;
				conner2.y = p2.y;
				conner2.x = i;
				return b;
			}
		}

	} // ɨ���н���

	return b;
}

// �����ť��Ӧ����
void CLLKButton::OnLButtonDown(UINT nFlags, CPoint point)
{

	if (firstBtn == NULL) // ��һ�ε����ťʱ
	{
		firstBtn = this;
		//firstBtn->ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
	}
	else if (firstBtn == this) // ���ε���İ�ť��ͬʱ,ȡ��ѡ��
	{
		//firstBtn->ModifyStyle(0, BS_DEFPUSHBUTTON);
		firstBtn = NULL;
	}
	else if (firstBtn->ID != this->ID) // �ڶ��ε����ť��ͼƬ����ͬʱ
	{
		firstBtn = this;
	}
	else if (firstBtn->ID == this->ID) // ���ε����ͼƬ��ͬ
	{
		if (LinkInLine(firstBtn->location, this->location) || OneCornerLink(firstBtn->location, this->location)
			|| TwoCornerLink(firstBtn->location, this->location)) // ����ͼƬ֮���������
		{
			secondBtn = this;
			game->OnPaint();
			firstBtn->ShowWindow(SW_HIDE); // ���ذ�ť
			secondBtn->ShowWindow(SW_HIDE);
			game->map[firstBtn->location.x][firstBtn->location.y] = 0;
			game->map[secondBtn->location.x][secondBtn->location.y] = 0;




			firstBtn->ID = 0;
			secondBtn->ID = 0;

			if (game->IsFinished()) // ���ͨ��
			{
				MessageBox(_T("��ϲͨ��������"), _T("ͨ��"));

				if (MessageBox(_T("�Ƿ񱣴��¼"), _T("��ʾ"), MB_YESNO) == IDYES)// �����¼
				{
					CStdioFile mFile;
					CFileException mExcept;
					if (!mFile.Open(_T("record.txt"), CFile::modeWrite, &mExcept))
						mFile.Open(_T("record.txt"), CFile::modeCreate | CFile::modeWrite, &mExcept);
					CString str;
					mFile.SeekToEnd();
					//����¼д���ļ��������
					CTime t = CTime::GetCurrentTime();
					CString s = t.Format(_T("%Y-%m-%d %H:%M:%S\n"));
					//MessageBox(_T("" + s));
					mFile.WriteString(s);
					s.Format(_T("%d\n"), 123); // 123 �滻Ϊ n
					mFile.WriteString(s);

				}
			}
			firstBtn = NULL;
			secondBtn = NULL;
		}
		else
		{
			firstBtn = NULL;
		}
	}

	game->RedrawWindow();
}


