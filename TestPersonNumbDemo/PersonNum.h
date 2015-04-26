//***********2015,04.21***********
//***遮挡压边条方法类CPersonNum***
//说明：针对480X320特定带有压边条的
//      类，手动指定压边条区域，处理
//      效果经调节参数100%正确。
//注意：我们的两个上下车的视频压边条
//      位置不一致，下车视频比上车
//      视频高10像素左右，这就要调节
//      压边条窗口位置。还有下车人的
//      速度不一致。
//********************************
#pragma once
#include "opencv/cv.h"
#include "opencv/highgui.h"
class CPersonNum //遮挡压边条方法类
{
public:
	CPersonNum();
	~CPersonNum();
	bool detectPersonNum(IplImage *);
	IplImage *GetFrameGray(){return m_framegray;};
	IplImage* GetFrameCanny(){return m_framecanny;};
	int GetPersonNums(){return m_personnum;};
	void setYBTArea(){m_rectybtArea = cvRect( 220, 210, 100, 25 );};//设置压边条计算位置 另外一个位置向上偏移10
	int m_personnum;//人数
private:
	CvRect m_rectybtArea;//压边条区域
	CvRect m_rectROI;//ROI区域 只是关注区域
	//判断前景参数标志位，只有当preflag是假时，curflag是真是才算有人
	bool m_preflag;
	bool m_curflag;
	int m_areacountcur;//代表连续多少张图片判断，可以解决上下车速度问题
	IplImage *m_framegray;//帧的灰度图像
	IplImage *m_framecanny;//canny结果
	const static int conStaPicTrd = 8;//代表连续多少张图片判断的阈值，这个可以根据上下车速度调整
};

