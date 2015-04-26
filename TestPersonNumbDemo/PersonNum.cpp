#include "stdafx.h"
#include "PersonNum.h"

//int CPersonNum::m_personnum=0;//人数初始化为0
CPersonNum::CPersonNum()
{
	m_preflag=false;
	m_curflag=false;
	m_areacountcur=0;
	m_rectybtArea = cvRect( 220, 150, 100, 25 );//ROI区域 中间压边条区域
	m_rectROI = cvRect( 170, 0, 200, 300 );//ROI区域 只是关注区域
	m_framecanny=NULL;
	m_framegray=NULL;
	m_personnum=0;//人数初始化为0
}
CPersonNum::~CPersonNum()
{
	if (m_framegray)
	{
		cvReleaseImage(&m_framegray);
	}
	if (m_framecanny)
	{
		cvReleaseImage(&m_framecanny);
	}
}
bool CPersonNum::detectPersonNum(IplImage *frame)
{

	if(!frame)
	{
		return false;
	}	
	if (m_framecanny==NULL)
	{
		m_framegray = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
		m_framecanny = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	}
	cvConvertImage(frame, m_framegray);
	//cvCopyImage(frame,frame_gray);
	cvSetImageROI(frame, m_rectROI );
	cvSetImageROI(m_framegray, m_rectROI );
	cvSetImageROI(m_framecanny, m_rectROI );
	memset(m_framecanny->imageData,0,m_framecanny->width*m_framecanny->height);
	cvCanny(m_framegray, m_framecanny, 190, 220, 3);

	cvResetImageROI( frame );
	cvResetImageROI( m_framegray );
	cvResetImageROI( m_framecanny );
	cvSaveImage("front.bmp",m_framecanny);

	//计算梯度面积
	//cvSetImageROI(frame_canny, rect );
	int area=0;
	for (int i=m_rectybtArea.y;i<m_rectybtArea.y+m_rectybtArea.height;++i)
		for (int j=m_rectybtArea.x;j<m_rectybtArea.x+m_rectybtArea.width;++j)
		{
			if (m_framecanny->imageData[i*m_framecanny->width+j])
				area++;
		}
		//std::cout<<area<<"  ";//边缘大小

		if (area<150)
		{
			m_areacountcur++;
		}
		else //if(areacountcur>8&&area>200)
		{
			m_areacountcur=0;
		}

		if (m_areacountcur>= conStaPicTrd)
		{
			m_curflag=true;
		}else
		{
			m_curflag=false;
		}
		if (m_preflag==false&&m_curflag==true)
		{  
			m_personnum++;
			//std::cout<<"检测到一人，总人数为："<<m_personnum<<std::endl;
		}
		m_preflag=m_curflag;

		/*cvShowImage("Video", frame);
		cvShowImage("Gray", m_framegray);
		cvShowImage("Canny", m_framecanny);
		char c = cvWaitKey(33);*/

}