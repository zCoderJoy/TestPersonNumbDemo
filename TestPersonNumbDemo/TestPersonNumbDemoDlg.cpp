
// TestPersonNumbDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestPersonNumbDemo.h"
#include "TestPersonNumbDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestPersonNumbDemoDlg 对话框



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


// CTestPersonNumbDemoDlg 消息处理程序

BOOL CTestPersonNumbDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_winThdReadVideo=NULL;
	m_cWndShow[0]=GetDlgItem(IDC_STATIC_ORIGIN);
	m_cWndShow[1]=GetDlgItem(IDC_STATIC_RESULT);
	m_hwndHeadNumber=GetDlgItem(IDC_EDIT_SHOWRESULT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestPersonNumbDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestPersonNumbDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestPersonNumbDemoDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,_T("*.mp4"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST/*|OFN_HIDEREADONLY*/
		,_T("video files (*.mp4;*.avi)|*.mp4;*.avi|ALL Files(*.*)|*.*||"),NULL); // 选项视频的约定
	dlg.m_ofn.lpstrTitle=_T("Open Video"); // 打开文件对话框的标题名
	if (dlg.DoModal()!=IDOK)
	{
		return; // 判断是否获得视频
	}
	m_spath=dlg.GetPathName(); // 获取视频路径

}
//创建线程
UINT ThreadProcessReadVideo(LPVOID pParam)
{
	CTestPersonNumbDemoDlg *l_pVPD2=(CTestPersonNumbDemoDlg *)pParam;
	CvCapture* capture= cvCaptureFromFile(l_pVPD2->m_spath);
	IplImage *frame;//抓取到的每一帧
	bool *t_bMask=NULL;
	int t_nPersonNumbs=0;
	MSG msg;//消息信息
	CvvImage target[2];
	CRect rect[2];//显示模块
	CDC* l_PostScreen=l_pVPD2->m_cWndShow[0]->GetDC();
	CDC* l_PostScreen2=l_pVPD2->m_cWndShow[1]->GetDC();
	HDC l_Hdc=l_PostScreen->GetSafeHdc();
	HDC l_Hdc2=l_PostScreen2->GetSafeHdc();
	l_pVPD2->m_cWndShow[0]->GetClientRect(&rect[0]);
	l_pVPD2->m_cWndShow[1]->GetClientRect(&rect[1]);
	bool flag=true,flag2=true;//表示选择上还是下统计人数
	l_pVPD2->m_PersonNum2.setYBTArea();//设置检测下车
	if( capture )
	{	
		
		while(1)
		{
			frame = cvQueryFrame(capture);
			
			if (!frame)
				return 0;
			//显示视频
			//cvvimage显示
			target[0].CopyOf(frame);
			target[0].DrawToHDC(l_Hdc,rect[0]);
			if (flag)
			{
				l_pVPD2->m_PersonNum.detectPersonNum(frame);
				//cvvimage显示
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
			//cout<<"检测到一人,总人数为："<<t_nPersonNumbs<<endl;
			CString str;
			if (t_nPersonNumbs)
			{
				flag2=false;
				str.Format("%d",t_nPersonNumbs);
				l_pVPD2->m_hwndHeadNumber->SetWindowTextA("上车检测进行中,目前总人数为："+str);
			}else
				if (t_nPersonNumbs2)
				{
					flag=false;
					str.Format("%d",t_nPersonNumbs2);
					l_pVPD2->m_hwndHeadNumber->SetWindowTextA("下车检测进行中,目前总人数为："+str);
				}else
				{
					str.Format("%d",0);
					l_pVPD2->m_hwndHeadNumber->SetWindowTextA("检测进行中,目前总人数为："+str);
				}
			
			
		
			if (PeekMessage(&msg,0,0,0,0))
			{
				AfxEndThread(0);//如果收到信息退出线程
				return 0;
			}
			Sleep(43);
			
		}
	}
//l_pVPD2->m_VideoPostProcess.ClimbDetect();//攀高检测
	return 0;
}

void CTestPersonNumbDemoDlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_winThdReadVideo!=NULL) 
	{
		GetDlgItem(IDC_BTN_START)->SetWindowTextA("检测开始");
		int i=PostThreadMessage(m_winThdReadVideo->m_nThreadID,WM_QUIT,0,0);
		m_winThdReadVideo=nullptr;
	}
	else
	{
		GetDlgItem(IDC_BTN_START)->SetWindowTextA("检测中");
		m_winThdReadVideo=AfxBeginThread(ThreadProcessReadVideo,this);
	}
}


void CTestPersonNumbDemoDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_winThdReadVideo!=NULL) 
	{
		PostThreadMessage(m_winThdReadVideo->m_nThreadID,WM_QUIT,0,0);
	}
	CDialogEx::OnOK();
}
