//***********2015,04.21***********
//***�ڵ�ѹ����������CPersonNum***
//˵�������480X320�ض�����ѹ������
//      �࣬�ֶ�ָ��ѹ�������򣬴���
//      Ч�������ڲ���100%��ȷ��
//ע�⣺���ǵ��������³�����Ƶѹ����
//      λ�ò�һ�£��³���Ƶ���ϳ�
//      ��Ƶ��10�������ң����Ҫ����
//      ѹ��������λ�á������³��˵�
//      �ٶȲ�һ�¡�
//********************************
#pragma once
#include "opencv/cv.h"
#include "opencv/highgui.h"
class CPersonNum //�ڵ�ѹ����������
{
public:
	CPersonNum();
	~CPersonNum();
	bool detectPersonNum(IplImage *);
	IplImage *GetFrameGray(){return m_framegray;};
	IplImage* GetFrameCanny(){return m_framecanny;};
	int GetPersonNums(){return m_personnum;};
	void setYBTArea(){m_rectybtArea = cvRect( 220, 210, 100, 25 );};//����ѹ��������λ�� ����һ��λ������ƫ��10
	int m_personnum;//����
private:
	CvRect m_rectybtArea;//ѹ��������
	CvRect m_rectROI;//ROI���� ֻ�ǹ�ע����
	//�ж�ǰ��������־λ��ֻ�е�preflag�Ǽ�ʱ��curflag�����ǲ�������
	bool m_preflag;
	bool m_curflag;
	int m_areacountcur;//��������������ͼƬ�жϣ����Խ�����³��ٶ�����
	IplImage *m_framegray;//֡�ĻҶ�ͼ��
	IplImage *m_framecanny;//canny���
	const static int conStaPicTrd = 8;//��������������ͼƬ�жϵ���ֵ��������Ը������³��ٶȵ���
};

