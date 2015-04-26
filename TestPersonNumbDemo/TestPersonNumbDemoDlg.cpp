
// TestPersonNumbDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestPersonNumbDemo.h"
#include "TestPersonNumbDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestPersonNumbDemoDlg �Ի���



CTestPersonNumbDemoDlg::CTestPersonNumbDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestPersonNumbDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestPersonNumbDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestPersonNumbDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CTestPersonNumbDemoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_START, &CTestPersonNumbDemoDlg::OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CTestPersonNumbDemoDlg ��Ϣ�������

BOOL CTestPersonNumbDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_winThdReadVideo=NULL;
	m_cWndShow[0]=GetDlgItem(IDC_STATIC_ORIGIN);
	m_cWndShow[1]=GetDlgItem(IDC_STATIC_RESULT);
	m_hwndHeadNumber=GetDlgItem(IDC_EDIT_SHOWRESULT);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestPersonNumbDemoDlg::OnPaint()
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
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestPersonNumbDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestPersonNumbDemoDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,_T("*.mp4"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST/*|OFN_HIDEREADONLY*/
		,_T("video files (*.mp4;*.avi)|*.mp4;*.avi|ALL Files(*.*)|*.*||"),NULL); // ѡ����Ƶ��Լ��
	dlg.m_ofn.lpstrTitle=_T("Open Video"); // ���ļ��Ի���ı�����
	if (dlg.DoModal()!=IDOK)
	{
		return; // �ж��Ƿ�����Ƶ
	}
	m_spath=dlg.GetPathName(); // ��ȡ��Ƶ·��

}
//�����߳�
UINT ThreadProcessReadVideo(LPVOID pParam)
{
	CTestPersonNumbDemoDlg *l_pVPD2=(CTestPersonNumbDemoDlg *)pParam;
	CvCapture* capture= cvCaptureFromFile(l_pVPD2->m_spath);
	IplImage *frame;//ץȡ����ÿһ֡
	bool *t_bMask=NULL;
	int t_nPersonNumbs=0;
	MSG msg;//��Ϣ��Ϣ
	CvvImage target[2];
	CRect rect[2];//��ʾģ��
	CDC* l_PostScreen=l_pVPD2->m_cWndShow[0]->GetDC();
	CDC* l_PostScreen2=l_pVPD2->m_cWndShow[1]->GetDC();
	HDC l_Hdc=l_PostScreen->GetSafeHdc();
	HDC l_Hdc2=l_PostScreen2->GetSafeHdc();
	l_pVPD2->m_cWndShow[0]->GetClientRect(&rect[0]);
	l_pVPD2->m_cWndShow[1]->GetClientRect(&rect[1]);
	bool flag=true,flag2=true;//��ʾѡ���ϻ�����ͳ������
	l_pVPD2->m_PersonNum2.setYBTArea();//���ü���³�
	if( capture )
	{	
		
		while(1)
		{
			frame = cvQueryFrame(capture);
			
			if (!frame)
				return 0;
			//��ʾ��Ƶ
			//cvvimage��ʾ
			target[0].CopyOf(frame);
			target[0].DrawToHDC(l_Hdc,rect[0]);
			if (flag)
			{
				l_pVPD2->m_PersonNum.detectPersonNum(frame);
				//cvvimage��ʾ
				target[1].CopyOf(l_pVPD2->m_PersonNum.GetFrameCanny());
				target[1].DrawToHDC(l_Hdc2,rect[1]);
			}
			if (flag2)
			{
				l_pVPD2->m_PersonNum2.detectPersonNum(frame);
				target[1].CopyOf(l_pVPD2->m_PersonNum2.GetFrameCanny());
				target[1].DrawToHDC(l_Hdc2,rect[1]);
			}
			
			
			t_nPersonNumbs=l_pVPD2->m_PersonNum.GetPersonNums();
			int t_nPersonNumbs2=l_pVPD2->m_PersonNum2.GetPersonNums();
			//cout<<"��⵽һ��,������Ϊ��"<<t_nPersonNumbs<<endl;
			CString str;
			if (t_nPersonNumbs)
			{
				flag2=false;
				str.Format("%d",t_nPersonNumbs);
				l_pVPD2->m_hwndHeadNumber->SetWindowTextA("�ϳ���������,Ŀǰ������Ϊ��"+str);
			}else
				if (t_nPersonNumbs2)
				{
					flag=false;
					str.Format("%d",t_nPersonNumbs2);
					l_pVPD2->m_hwndHeadNumber->SetWindowTextA("�³���������,Ŀǰ������Ϊ��"+str);
				}else
				{
					str.Format("%d",0);
					l_pVPD2->m_hwndHeadNumber->SetWindowTextA("��������,Ŀǰ������Ϊ��"+str);
				}
			
			
		
			if (PeekMessage(&msg,0,0,0,0))
			{
				AfxEndThread(0);//����յ���Ϣ�˳��߳�
				return 0;
			}
			Sleep(43);
			
		}
	}
//l_pVPD2->m_VideoPostProcess.ClimbDetect();//�ʸ߼��
	return 0;
}

void CTestPersonNumbDemoDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_winThdReadVideo!=NULL) 
	{
		GetDlgItem(IDC_BTN_START)->SetWindowTextA("��⿪ʼ");
		int i=PostThreadMessage(m_winThdReadVideo->m_nThreadID,WM_QUIT,0,0);
		m_winThdReadVideo=nullptr;
	}
	else
	{
		GetDlgItem(IDC_BTN_START)->SetWindowTextA("�����");
		m_winThdReadVideo=AfxBeginThread(ThreadProcessReadVideo,this);
	}
}


void CTestPersonNumbDemoDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_winThdReadVideo!=NULL) 
	{
		PostThreadMessage(m_winThdReadVideo->m_nThreadID,WM_QUIT,0,0);
	}
	CDialogEx::OnOK();
}
