
// TestPersonNumbDemoDlg.h : ͷ�ļ�
//
#pragma once
#include "PersonNum.h"
#include "CvvImage.h"
// CTestPersonNumbDemoDlg �Ի���
class CTestPersonNumbDemoDlg : public CDialogEx
{
// ����
public:
	CTestPersonNumbDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTPERSONNUMBDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//��Ƶ·��
	CString m_spath;
	//����Ƶ�����߳�
	CWinThread *m_winThdReadVideo;
	//������
	CPersonNum m_PersonNum;
	CPersonNum m_PersonNum2;//�ڶ���λ�ü���
	//��ʾ���ھ��
	CWnd *m_cWndShow[2];
	//��ʾ������Ϣ
	CWnd *m_hwndHeadNumber;
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnStart();
	virtual void OnOK();
};
