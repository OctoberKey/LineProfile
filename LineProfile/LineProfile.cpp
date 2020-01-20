#include "stdafx.h"
#include "LineProfile.h"
#include <opencv2/opencv.hpp>

/*
pt: 待旋转的点
rotM: 旋转矩阵
*/
cv::Point2f rotate(const cv::Point2f& pt, const cv::Mat& rotM)
{
  cv::Point2f rotPt;
  rotPt.x = *rotM.ptr<double>(0, 0) * pt.x + *rotM.ptr<double>(0, 1) * pt.y + *rotM.ptr<double>(0, 2) * 1;
  rotPt.y = *rotM.ptr<double>(1, 0) * pt.x + *rotM.ptr<double>(1, 1) * pt.y + *rotM.ptr<double>(1, 2) * 1;
  return rotPt;
}

cv::Point2f rotate(const cv::Point2f& pt,
  double a00, double a01, double a02,
  double a10, double a11, double a12)
{
  return cv::Point2f(a00 * pt.x + a01 * pt.y + a02 * 1,
    a10 * pt.x + a11 * pt.y + a12 * 1);
}

void func(cv::Mat& src,                 /* 输入图像 */
  const cv::RotatedRect& rect,  /* ROI区域 */
  /*bool reverse,                 /* 是否顺这ROI角度 */
  /*bool w2b,                     /* 白到黑 */
  float segmentWidth,           /* 搜索线的宽 */
  float movement,               /* 搜索线间距 */
  float offset                  /* 起始偏移量 */
)
{
  // 假设一条横线进行了反向旋转后变成了ROI的中心横线
  cv::Mat matrix = cv::getRotationMatrix2D(rect.center, -rect.angle, 1.0);
  double a00 = *matrix.ptr<double>(0, 0);
  double a01 = *matrix.ptr<double>(0, 1);
  double a02 = *matrix.ptr<double>(0, 2);
  double a10 = *matrix.ptr<double>(1, 0);
  double a11 = *matrix.ptr<double>(1, 1);
  double a12 = *matrix.ptr<double>(1, 2);

  cv::Point2f lMid(rect.center.x - rect.size.width / 2, rect.center.y);
  cv::Point2f rMid(rect.center.x + rect.size.width / 2, rect.center.y);

  double left = rect.center.x - rect.size.width / 2;
  double right = rect.center.x + rect.size.width / 2;
  double top = rect.center.y - rect.size.height / 2;
  double bottom = rect.center.y + rect.size.height / 2;
  double height = rect.size.height;
  double width = rect.size.width;
  
  /*
    中间：offset + segmentWidth / 2 + movement * n
    起始：offset + movement * n
    中止：offset + movement * n + segmentWidth - 1
    offset + movement * n + segmentWidth - 1 = height - 1
    n = (height - offset - segmentWidth) / movement
   */
  int segmentCnt = (height - offset - segmentWidth) / movement + 1;
  cv::Mat rowSignal = cv::Mat::zeros(1, height, CV_8UC1);
  uchar* pn = &rowSignal.ptr<uchar>(0)[0];
  for (int n = 0; n < segmentCnt; ++n)
  {
    for (int row = offset + movement * n; row < offset + movement * n + segmentWidth; ++row)
    {
      pn[row] = 1;
    }
  }

  cv::Mat line = cv::Mat::zeros(rect.size, CV_32FC4);
  cv::Point2f pt;
  for (int row = 0; row < rect.size.height; row++)
  {
    if (*pn++ == 0)
      continue;

    cv::Vec4f* p = line.ptr<cv::Vec4f>(row);
    for (int col = 0; col < rect.size.width; col++)
    {
      double x = left + col;
      double y = rect.center.y;

      pt.x = x;
      pt.y = y;
      pt = rotate(pt, a00, a01, a02, a10, a11, a12);
      //pt = rotate(lMid, matrix);

      p[col][0] = pt.x;
      p[col][1] = pt.y;

      if (pt.x >= 0 && pt.y >= 0)
      {
        int x1 = (int)pt.x;
        int y1 = (int)pt.y;
        int x2 = x1 + 1;
        int y2 = y1 + 1;

#if 0
        cv::Mat x_m = (cv::Mat_<double>(1, 2) << 1 - (x - x1), x - x1);
        cv::Mat y_m = (cv::Mat_<double>(2, 1) << 1 - (y - y1), y - y1);
        cv::Mat v_m = (cv::Mat_<double>(2, 2) <<
          *src.ptr<uchar>(y1, x1),
          *src.ptr<uchar>(y2, x1),
          *src.ptr<uchar>(y1, x2),
          *src.ptr<uchar>(y2, x2)
          );
        cv::Mat mm = x_m * v_m * y_m;
        line.ptr<cv::Vec3d>(row)[col][2] = mm.at<double>(0, 0);
#else
        double Q11 = *src.ptr<uchar>(y1, x1);
        double Q12 = *src.ptr<uchar>(y2, x1);
        double Q21 = *src.ptr<uchar>(y1, x2);
        double Q22 = *src.ptr<uchar>(y2, x2);
        double x_y1 = (x2 - pt.x) / (x2 - x1) * Q11 + (pt.x - x1) / (x2 - x1) * Q21;
        double x_y2 = (x2 - pt.x) / (x2 - x1) * Q12 + (pt.x - x1) / (x2 - x1) * Q22;
        double x_y = (y2 - pt.y) / (y2 - y1) * x_y1 + (pt.y - y1) / (y2 - y1) * x_y2;
        p[col][2] = x_y;
#endif
      }
      else
      {
        line.ptr<cv::Vec4f>(row)[col][2] = std::numeric_limits<double>::quiet_NaN();
      }
    }
  }
}

LineProfile::LineProfile(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);

  cv::TickMeter tm;
  tm.start();
  cv::Mat src = cv::imread(R"(test.bmp)", cv::IMREAD_UNCHANGED);
  tm.stop();
  double ms = tm.getTimeMilli();

  QMessageBox::information(this, "", QString::number(ms));

  tm.start();
  func(src, cv::RotatedRect(cv::Point2f(1840, 1130), cv::Size2f(800, 800), 5), 3, 5, 0);
  tm.stop();
  ms = tm.getTimeMilli();

  QMessageBox::information(this, "", QString::number(ms));
}
