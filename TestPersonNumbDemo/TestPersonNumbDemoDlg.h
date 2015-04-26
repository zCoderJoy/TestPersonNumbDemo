
// TestPersonNumbDemoDlg.h : 头文件
//
#pragma once
#include "PersonNum.h"
#include "CvvImage.h"
// CTestPersonNumbDemoDlg 对话框
class CTestPersonNumbDemoDlg : public CDialogEx
{
// 构造
public:
	CTestPersonNumbDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTPERSONNUMBDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//视频路径
	CString m_spath;
	//读视频处理线程
	CWinThread *m_winThdReadVideo;
	//数人数
	CPersonNum m_PersonNum;
	CPersonNum m_PersonNum2;//第二个位置计算
	//显示窗口句柄
	CWnd *m_cWndShow[2];
	//显示人数消息
	CWnd *m_hwndHeadNumber;
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnStart();
	virtual void OnOK();
};
