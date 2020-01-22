#include "stdafx.h"
#include "LineProfile.h"
#include <opencv2/opencv.hpp>
#include <sstream>

/*
pt: 待旋转的点
rotM: 旋转矩阵
*/
cv::Point2f rotate(float x, float y, const cv::Mat/*Matx23d*/& rotM)
{
  cv::Point2f rotPt;
  rotPt.x = *rotM.ptr<double>(0, 0) * x + *rotM.ptr<double>(0, 1) * y + *rotM.ptr<double>(0, 2) * 1;
  rotPt.y = *rotM.ptr<double>(1, 0) * x + *rotM.ptr<double>(1, 1) * y + *rotM.ptr<double>(1, 2) * 1;
  return rotPt;
}

cv::Point2f rotate(const cv::Point2f& pt, const cv::Mat& rotM)
{
  return rotate(pt.x, pt.y, rotM);
}

cv::Point2f rotate(const cv::Point2f& pt,
                   double a00, double a01, double a02,
                   double a10, double a11, double a12)
{
  return cv::Point2f(a00 * pt.x + a01 * pt.y + a02 * 1,
                     a10 * pt.x + a11 * pt.y + a12 * 1);
}

class LineEdgeDectector
{
public:
  LineEdgeDectector() {}

  LineEdgeDectector(const int width,
                    const int height,
                    const cv::RotatedRect& roi,
                    const int traceDirection,
                    const int transitionDirection,
                    const int segmentWidth,
                    const int startOffset,
                    const int step,
                    const int segmentCountMax,
                    const float threshold,
                    const int filterSize,
                    const float filterSigma)
  {
    init(width,
         height,
         roi,
         traceDirection,
         transitionDirection,
         segmentWidth,
         startOffset,
         step,
         segmentCountMax,
         threshold,
         filterSize,
         filterSigma);
  }

  void init(const int width,
            const int height,
            const cv::RotatedRect& roi,
            const int traceDirection,
            const int transitionDirection,
            const int segmentWidth,
            const int startOffset,
            const int step,
            const int segmentCountMax,
            const float threshold,
            const int filterSize,
            const float filterSigma)
  {
    _widthImage = width;
    _heightImage = height;
    _roi = roi;
    _widthRoi = _roi.size.width;
    _heightRoi = _roi.size.height;
    _leftRoi = _roi.center.x - _widthRoi / 2;
    _topRoi = _roi.center.y - _heightRoi / 2;
    _traceDirection = traceDirection;
    _transitionDirection = transitionDirection;
    _segmentWidth = segmentWidth;
    _startOffset = startOffset;
    _step = step;
    _segmentCountMax = segmentCountMax;
    _threshold = threshold;
    _filterSize = filterSize;
    _filterSigma = filterSigma;

    _segmentCount = (_heightRoi - _startOffset - _segmentWidth) / _step + 1;
    if (_segmentCount < 0)
      _segmentCount = 0;

    _pos = cv::Mat::zeros(_heightRoi, _widthRoi, CV_32FC2);
    _v = cv::Mat::zeros(_heightRoi, _widthRoi, CV_32FC1);
    _mean = cv::Mat::zeros(_heightRoi, _widthRoi, CV_32FC1);
    _filtered = cv::Mat::zeros(_heightRoi, _widthRoi, CV_32FC1);
    _derivative = cv::Mat::zeros(_heightRoi, _widthRoi, CV_32FC1);
    // 第一列表示此行会被平均的次数，后面是搜索线的中心行
    _rowIndex = cv::Mat::zeros(_heightRoi, _segmentCount + 1, CV_16UC1);
    // 第一列表示OK峰值的个数，后面是峰值所在列索引
    _peakIndex = cv::Mat::zeros(_heightRoi, _segmentCount + 1, CV_32FC3);

    if (_filterSize > 1)
      _gaussianKernel = cv::getGaussianKernel(_filterSize / 2 * 2 + 1, _filterSigma, CV_32F);

    for (int n = 0; n < _segmentCount; ++n)
    {
      for (int row = _startOffset + _step * n; row < _startOffset + _step * n + _segmentWidth; ++row)
      {
        int i = ++_rowIndex.ptr<ushort>(row)[0];
        _rowIndex.ptr<ushort>(row)[i] = _startOffset + _step * n + _segmentWidth / 2;
      }
    }

    cv::Mat matrix = cv::getRotationMatrix2D(roi.center, -roi.angle, 1.0);
    for (int row = 0; row < _heightRoi; ++row)
    {
      for (int col = 0; col < _widthRoi; ++col)
      {
        cv::Point2f pt = rotate(_leftRoi + col, _topRoi + row, matrix);
        _pos.ptr<cv::Vec2f>(row)[col][0] = pt.x;
        _pos.ptr<cv::Vec2f>(row)[col][1] = pt.y;
      }
    }
  }

  void process(const cv::Mat& src)
  {
    float maxVal = std::numeric_limits<float>::lowest();
    for (int row = 0; row < _heightRoi; ++row)
    {
      for (int col = 0; col < _widthRoi; ++col)
      {
        float x = _pos.ptr<cv::Vec2f>(row)[col][0];
        float y = _pos.ptr<cv::Vec2f>(row)[col][1];

        int x1 = (int)x;
        int y1 = (int)y;
        int x2 = x1 + 1;
        int y2 = y1 + 1;
        if (x1 >= 0 && x1 < src.cols && y1 >= 0 && y1 < src.rows &&
            x2 >= 0 && x2 < src.cols && y2 >= 0 && y2 < src.rows)
        {
          // 双线性插值
          double Q11 = src.ptr<uchar>(y1)[x1];
          double Q12 = src.ptr<uchar>(y2)[x1];
          double Q21 = src.ptr<uchar>(y1)[x2];
          double Q22 = src.ptr<uchar>(y2)[x2];

          double x_y1 = (x2 - x) / (x2 - x1) * Q11 + (x - x1) / (x2 - x1) * Q21;
          double x_y2 = (x2 - x) / (x2 - x1) * Q12 + (x - x1) / (x2 - x1) * Q22;
          double x_y = (y2 - y) / (y2 - y1) * x_y1 + (y - y1) / (y2 - y1) * x_y2;

          // 把值加到均值里
          for (int i = 1; i <= _rowIndex.ptr<ushort>(row)[0]; ++i)
          {
            int r = _rowIndex.ptr<ushort>(row)[i];
            _mean.ptr<float>(r)[col] += x_y;
          }

          _v.ptr<float>(row)[col] = x_y;

          int n = (row - _startOffset - _segmentWidth + 1) / _step;
          int m = (row - _startOffset - _segmentWidth + 1) % _step;
          // 线段宽度的最后一行，取均值
          if (m == 0 && n >= 0)
          {
            int r = _startOffset + _step * n + _segmentWidth / 2;
            _mean.ptr<float>(r)[col] /= _segmentWidth;

            // 滤波
            int c = col - _filterSize + 1 + _filterSize / 2;
            // 需要滤波
            if (_filterSize > 1)
            {
              // 完整滤波
              if (col >= _filterSize - 1)
              {
                float mean = 0;
                for (int i = 0; i < _filterSize; ++i)
                {
                  int cc = col - _filterSize + i + 1;
                  mean += _mean.ptr<float>(r)[cc] * _gaussianKernel.ptr<float>(i)[0];
                }
                _filtered.ptr<float>(r)[c] = mean;

                // 求导
                if (c > _filterSize / 2 + 1 && c + 1 < _widthRoi)
                {
                  _derivative.ptr<float>(r)[c - 1] = _filtered.ptr<float>(r)[c - 2] - _filtered.ptr<float>(r)[c];
                }
              }

              // 首尾还没有滤波，直接使用原数据
              // TODO: 增加border, border_size = _filterSize / 2
              if (col == _widthRoi - 1)
              {
                for (int i = 0; i < _filterSize / 2; ++i)
                {
                  _filtered.ptr<float>(r)[i] = _mean.ptr<float>(r)[i];
                  _filtered.ptr<float>(r)[_widthRoi - i - 1] = _mean.ptr<float>(r)[_widthRoi - i - 1];
                }

                for (int i = 1; i < _filterSize / 2 + 1; ++i)
                {
                  _derivative.ptr<float>(r)[i] = _filtered.ptr<float>(r)[i - 1] - _filtered.ptr<float>(r)[i + 1];
                  _derivative.ptr<float>(r)[_widthRoi - i - 1] =
                    _filtered.ptr<float>(r)[_widthRoi - i - 1 - 1] - _filtered.ptr<float>(r)[_widthRoi - i - 1 + 1];
                }
              }
            }
            // 不滤波了
            else
            {
              _filtered.ptr<float>(r)[c] = _mean.ptr<float>(r)[c];

              // 求导
              if (c - 1 > 0 && c + 1 < _widthRoi)
              {
                _derivative.ptr<float>(r)[c] = _filtered.ptr<float>(r)[c - 1] - _filtered.ptr<float>(r)[c + 1];
              }
            }
          }
        }
        else
        {
          // TODO: Out of image boundary
        }
      }
    }

    // 顺着角度方向
    if (_traceDirection == 0)
    {
      for (int n = 0; n < _segmentCount; ++n)
      {
        int row = _startOffset + _step * n + _segmentWidth / 2;
        for (int col = 1; col < _widthRoi - 1; ++col)
        {
          float v = _derivative.ptr<float>(row)[col];
          float v_m1 = _derivative.ptr<float>(row)[col - 1];
          float v_p1 = _derivative.ptr<float>(row)[col + 1];
          // 明到暗，倒数为负数
          if (_transitionDirection == 0)
          {
            if (v < -_threshold && v <= v_m1 && v <= v_p1)
            {
              int i = ++_peakIndex.ptr<ushort>(row)[0];
              _peakIndex.ptr<ushort>(row)[i] = col;
            }
          }
          // 暗到明，倒数为正数
          else
          {
            if (v > +-_threshold && v >= v_m1 && v >= v_p1)
            {
              int i = ++_peakIndex.ptr<ushort>(row)[0];
              _peakIndex.ptr<ushort>(row)[i] = col;
            }
          }
        }
      }
    }
    // 逆着角度方向
    else
    {
      for (int n = 0; n < _segmentCount; ++n)
      {
        int row = _startOffset + _step * n + _segmentWidth / 2;
        for (int col = _widthRoi - 2; col > 0; --col)
        {
          float v = _derivative.ptr<float>(row)[col];
          float v_m1 = _derivative.ptr<float>(row)[col - 1];
          float v_p1 = _derivative.ptr<float>(row)[col + 1];
          // 明到暗，倒数为负数
          if (_transitionDirection == 0)
          {
            if (v < -_threshold && v <= v_m1 && v <= v_p1)
            {
              _peakIndex.ptr<cv::Vec3f>(row)[0][0] += 1;
              int i = (int)(_peakIndex.ptr<cv::Vec3f>(row)[0][0] + 0.5);

              //////////////////////////////////////////////////////////////////////////
              double x1 = col - 1;
              double x2 = col;
              double x3 = col + 1;
              double y1 = v_m1;
              double y2 = v;
              double y3 = v_p1;
              double x0;
              double y0;

              if (y2 == y1 || y2 == y3)
              {
                x0 = x2;
                y0 = y2;
              }
              else
              {
                double a = -((x1 - x2) * (y3 - y1) - (x3 - x1) * (y1 - y2)) / ((x1 - x2) * (x2 - x3) * (x3 - x1));
                double b = (y1 - y2 - a * (x1 * x1 - x2 * x2)) / (x1 - x2);
                double c = y1 - a * x1 * x1 - b * x1;
                x0 = -b / (2 * a);
                y0 = (4 * a * c - b * b) / (4 * a);
                qDebug() << x0 << "," << y0;
              }
              _peakIndex.ptr<cv::Vec3f>(row)[i][0] = x0;
              _peakIndex.ptr<cv::Vec3f>(row)[i][1] = y0;
              //////////////////////////////////////////////////////////////////////////
            }
          }
          // 暗到明，倒数为正数
          else
          {
            if (v > +_threshold && v >= v_m1 && v >= v_p1)
            {
              int i = ++_peakIndex.ptr<ushort>(row)[0];
              _peakIndex.ptr<ushort>(row)[i] = col;
            }
          }
        }
      }
    }
  }

protected:
  // 宽度
  int _widthImage;
  // 高度
  int _heightImage;
  // 感兴趣区域：中心 + 宽 + 高 + 角度
  cv::RotatedRect _roi;
  int _widthRoi;
  int _heightRoi;
  float _leftRoi;
  float _topRoi;
  // 查找方向: 0 - ROI角度同方向; 1 - ROI角度反方向
  int _traceDirection;
  // 边缘类型: 0 - 明到暗; 1 - 暗到明
  int _transitionDirection;
  // 垂直于查找方向的宽度，用于平均的像素个数
  int _segmentWidth;
  // 起始偏移量
  int _startOffset;
  // 查找线段间隔
  int _step;
  // 查找线段的数量
  int _segmentCount;
  // 最大线段数量
  int _segmentCountMax;
  // 边缘强度阈值
  float _threshold;
  // 高斯滤波核大小
  int _filterSize;
  // 高斯滤波西格玛
  float _filterSigma;
  // 高斯滤波核
  cv::Mat _gaussianKernel;
  // 为方便调试，使用cv::Mat做为数据结构，调试时可使用Image Watch观察变量值
  // 延查找方向的x坐标
  //float* _x;
  // 延查找方向的y坐标
  //float* _y;
  cv::Mat _pos;
  // 延查找方向双线性插值后的值
  //float* _v;
  cv::Mat _v;
  // 延垂直方向取平均后的值
  //float* _mean;
  cv::Mat _mean;
  //
  cv::Mat _filtered;
  // 延查找方向进行求导后的值
  //float* _derivative;
  cv::Mat _derivative;
  // 查找线段的中心索引
  //int* _rowIndex;
  cv::Mat _rowIndex;
  // 
  cv::Mat _peakIndex;
  // TODO: 增加边缘感度，百分比，比阈值小，抛物线顶点比阈值大
};

cv::Mat func(cv::Mat& src,                 /* 输入图像 */
             const cv::RotatedRect& rect,  /* ROI区域 */
             bool reverse,                 /* 是否顺这ROI角度 */
             bool w2b,                     /* 白到黑 */
             float segmentWidth,           /* 搜索线的宽 */
             float movement,               /* 搜索线间距 */
             float offset,                  /* 起始偏移量 */
             float threshold                /* 边缘阈值*/
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

  //cv::Point2f lMid(rect.center.x - rect.size.width / 2, rect.center.y);
  //cv::Point2f rMid(rect.center.x + rect.size.width / 2, rect.center.y);

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
      if (pn[row] == 1)
      {
        continue;
      }
      else
      {
        pn[row] = 1;
      }
    }
  }

  // 存储扫描线上点的坐标和双线性插值算出来的结果
  cv::Mat line = cv::Mat::zeros(rect.size, CV_32FC4);
  // 插值计算出来的ROI图像
  cv::Mat lineImage = cv::Mat::zeros(rect.size, CV_32FC1);
  // 扫描线横向取均值后的图像
  cv::Mat line_average = cv::Mat::zeros(segmentCnt, width, CV_32FC1);
  // 扫描线纵向滤波后的图像
  cv::Mat line_blur = cv::Mat::zeros(segmentCnt, width, CV_32FC1);
  // 求导后的图像
  cv::Mat line_derivative = cv::Mat::zeros(segmentCnt, width, CV_32FC1);
  cv::Point2f pt;
  for (int row = 0; row < rect.size.height; row++)
  {
    if (*pn++ == 0)
      continue;

    cv::Vec4f* pVec4f = line.ptr<cv::Vec4f>(row);
    float* puc = lineImage.ptr<float>(row);
    for (int col = 0; col < rect.size.width; col++)
    {
      double x = left + col;
      double y = top + row;

      pt.x = x;
      pt.y = y;
      pt = rotate(pt, a00, a01, a02, a10, a11, a12);

      if (pt.x >= 0 && pt.y >= 0)
      {
        int x1 = (int)pt.x;
        int y1 = (int)pt.y;
        int x2 = x1 + 1;
        int y2 = y1 + 1;

        double Q11 = *src.ptr<uchar>(y1, x1);
        double Q12 = *src.ptr<uchar>(y2, x1);
        double Q21 = *src.ptr<uchar>(y1, x2);
        double Q22 = *src.ptr<uchar>(y2, x2);
        double x_y1 = (x2 - pt.x) / (x2 - x1) * Q11 + (pt.x - x1) / (x2 - x1) * Q21;
        double x_y2 = (x2 - pt.x) / (x2 - x1) * Q12 + (pt.x - x1) / (x2 - x1) * Q22;
        double x_y = (y2 - pt.y) / (y2 - y1) * x_y1 + (pt.y - y1) / (y2 - y1) * x_y2;

        puc[col] = x_y;
        pVec4f[col][0] = pt.x;
        pVec4f[col][1] = pt.y;
        pVec4f[col][2] = x_y;
      }
      else
      {
        puc[col] = 0;
      }
    }
  }

  // 横向平均
  for (int n = 0; n < segmentCnt; ++n)
  {
    float* average = line_average.ptr<float>(n);
    for (int row = offset + movement * n; row < offset + movement * n + segmentWidth; ++row)
    {
      float* data = lineImage.ptr<float>(row);
      for (int col = 0; col < width; ++col)
      {
        average[col] += data[col];
      }
    }
  }
  line_average /= 3;

  // 纵向平滑
  const int kernelSize = 3; // 必须大于segment的长度
  cv::Mat kernel = cv::getGaussianKernel(kernelSize, 0.5, CV_32F);
  float* pK = kernel.ptr<float>(0);
  for (int row = 0; row < segmentCnt; ++row)
  {
    float* average = line_average.ptr<float>(row);
    float* blur = line_blur.ptr<float>(row);
    int col = 0;

    for (col = kernelSize / 2; col < width - kernelSize / 2; ++col)
    {
      float bb = 0;
      for (int i = 0; i < kernelSize; ++i)
      {
        bb += pK[i] * average[col - kernelSize / 2 + i];
      }
      blur[col] = bb;
    }

    for (col = 0; col < kernelSize / 2; ++col)
    {
      blur[col] = blur[kernelSize / 2 * 2 - col];
    }

    for (col = width - kernelSize / 2; col < width; ++col)
    {
      blur[col] = blur[((int)width - kernelSize / 2 - 1) * 2 - col];
    }
  }

  // 求导
  cv::Mat maxPos = cv::Mat::zeros(segmentCnt, width, CV_32FC3);
  if (!reverse)
  {
    for (int row = 0; row < segmentCnt; ++row)
    {
      float* pd = line_derivative.ptr<float>(row);
      float* pb = line_average.ptr<float>(row);
      cv::Vec3f* pVec3f = maxPos.ptr<cv::Vec3f>(row);
      cv::Vec4f* pVec4f = line.ptr<cv::Vec4f>(row);
      for (int col = 1; col < width - 1; ++col)
      {
        pd[col] = pb[col + 1] - pb[col - 1];
        if (pd[col] > threshold && pVec3f[col][2] < 1)
        {
          pVec3f[col][0] = pVec4f[col][0];
          pVec3f[col][1] = pVec4f[col][1];
          pVec3f[col][2] = 2;
        }
      }
    }
  }
  else
  {
    for (int row = 0; row < segmentCnt; ++row)
    {
      float* pd = line_derivative.ptr<float>(row);
      float* pb = line_average.ptr<float>(row);
      for (int col = width - 1; col > 0; --col)
      {
        pd[col] = pb[col + 1] - pb[col - 1];
      }
    }
  }

  // TODO: 横向 y 也需要修正位置
  // TODO: 找出符合要求的点的位置
  // TODO: 抛物线求最大值位置
  /*
  double a = -((x1 - x2) * (y3 - y1) - (x3 - x1) * (y1 - y2)) / ((x1 - x2) * (x2 - x3) * (x3 - x1));
  double b = (y1 - y2 - a * (x1 * x1 - x2 * x2)) / (x1 - x2);
  double c = y1 - a * x1 * x1 - b * x1;
  double x0 = -b / (2 * a);
  double y0 = (4 * a * c - b * b) / (4 * a);
  peak[i] = y0;
  xx[i] = x0;
  */

  return lineImage;
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
  qDebug() << "cv::imread " << ms << " ms";

  //for (int i = 0; i < 360; ++i)
  {
    //*cv::Mat m = */func(src, cv::RotatedRect(cv::Point2f(1840, 1130), cv::Size2f(800, 800), 5/*i*/), true, true, 3, 5, 0, 40.f);
    //     std::stringstream ss;
    //     ss << i << ".bmp";
    //     cv::imwrite(ss.str(), m);
  }

  LineEdgeDectector d;
  cv::RotatedRect roi(cv::Point2f(1840, 1130), cv::Size2f(800, 800), 5);

  tm.reset();
  tm.start();
  d.init(src.cols, src.rows, roi, 1, 0, 3, 0, 3, -1, 80, 3, 0.8);
  tm.stop();
  ms = tm.getTimeMilli();
  qDebug() << "LineEdgeDectector::init " << ms << " ms";

  tm.reset();
  tm.start();
  d.process(src);
  tm.stop();
  ms = tm.getTimeMilli();
  qDebug() << "LineEdgeDectector::process " << ms << " ms";
}
