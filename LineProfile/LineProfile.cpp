#include "stdafx.h"
#include "LineProfile.h"
#include <opencv2/opencv.hpp>
#include <sstream>

/*
pt: ����ת�ĵ�
rotM: ��ת����
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

inline void mean_xy(const std::vector<cv::Point2f> &line, double &mean_x, double &mean_y)
{
  int size = line.size();
  mean_x = 0.0;
  mean_y = 0.0;
  for (int i = 0; i < size; i++)
  {
    mean_x += line[i].x;
    mean_y += line[i].y;
  }
  mean_x /= size;
  mean_y /= size; //���ˣ�������� x y �ľ�ֵ
}

inline void weightedMean_xy(const std::vector<cv::Point2f> &line,
                            double &mean_x, double &mean_y,
                            double tau, double a, double b, double c)
{
  int size = line.size();
  mean_x = 0.0;
  mean_y = 0.0;
  double sum_wx = 0, sum_wy = 0, sum_w = 0;
  for (int i = 0; i < size; i++)
  {
    double x = line[i].x, y = line[i].y;
    double d = abs(a * x + b * y + c);
    double w = d < tau ? 1 : tau / d;
    sum_wx += w * w * x;
    sum_wy += w * w * y;
    sum_w += w * w;
  }
  mean_x = sum_wx / sum_w;
  mean_y = sum_wy / sum_w; //���ˣ�������� x y �ľ�ֵ
}
inline void Dxxyyxy(const std::vector<cv::Point2f> &line,
                    double mx, double my,
                    double &Dxx, double &Dxy, double &Dyy)
{
  int size = line.size();
  for (int i = 0; i < size; i++)
  {
    double x = line[i].x;
    double y = line[i].y;
    Dxx += (x - mx) * (x - mx);
    Dxy += (x - mx) * (y - my);
    Dyy += (y - my) * (y - my);
  }
}
inline void weightedDxxxyyy(const std::vector<cv::Point2f> &line,
                            double mx, double my,
                            double &Dxx, double &Dxy, double &Dyy,
                            double tau, double a, double b, double c)
{
  int size = line.size();
  for (int i = 0; i < size; i++)
  {
    double x = line[i].x, y = line[i].y;
    double d = abs(a * x + b * y + c);
    double w = d < tau ? 1 : tau / d;
    w = w * w;
    Dxx += w * (x - mx) * (x - mx);
    Dxy += w * (x - mx) * (y - my);
    Dyy += w * (y - my) * (y - my);
  }
}

/**
 * @brief lineFit ��С���˷���� ax + by + c = 0 ��ֱ��.
 *  ���� a �� b ���� a^2 + b^2 = 1����ϵ��о��ǵ㵽ֱ�ߵĴ�ֱ����ƽ������С������ͨ�������µ�һԪ���Իع顣
 * @param points �������
 * @param [out] a ������ϵ��
 * @param [out] b ������ϵ��
 * @param [out] c ������ϵ��
 */
bool lineFit(const std::vector<cv::Point2f> &points, double &a, double &b, double &c)
{
  int size = points.size();
  if (size == 0)
  {
    a = 0;
    b = 0;
    c = 0;
    return false;
  }
  double x_mean = 0;
  double y_mean = 0;
  mean_xy(points, x_mean, y_mean);

  double Dxx = 0, Dxy = 0, Dyy = 0;
  Dxxyyxy(points, x_mean, y_mean, Dxx, Dxy, Dyy);

  double lambda = ((Dxx + Dyy) - sqrt((Dxx - Dyy) * (Dxx - Dyy) + 4 * Dxy * Dxy)) / 2.0;
  double den = sqrt(Dxy * Dxy + (lambda - Dxx) * (lambda - Dxx));

  if (fabs(den) < 1e-5)
  {
    if (fabs(Dxx / Dyy - 1) < 1e-5) //��ʱû��һ�������ֱ�߷����޷����
    {
      return false;
    }
    else
    {
      a = 1;
      b = 0;
      c = -x_mean;
    }
  }
  else
  {
    a = Dxy / den;
    b = (lambda - Dxx) / den;
    c = -a * x_mean - b * y_mean;
  }
  return true;
}

#if 0
bool weightedLineFitOneStep(const std::vector<cv::Point2f> &line, double &a, double &b, double &c, double tau)
{
  int size = line.size();
  if (size == 0)
  {
    a = 0;
    b = 0;
    c = 0;
    return false;
  }
  double x_mean = 0;
  double y_mean = 0;
  weightedMean_xy(line, x_mean, y_mean, tau, a, b, c);
  double Dxx = 0, Dxy = 0, Dyy = 0;
  weightedDxxxyyy(line, x_mean, y_mean, Dxx, Dxy, Dyy, tau, a, b, c);

  double lambda = ((Dxx + Dyy) - sqrt((Dxx - Dyy) * (Dxx - Dyy) + 4 * Dxy * Dxy)) / 2.0;
  double den = sqrt(Dxy * Dxy + (lambda - Dxx) * (lambda - Dxx));

  if (fabs(den) < 1e-5)
  {
    if (fabs(Dxx / Dyy - 1) < 1e-5) //��ʱû��һ�������ֱ�߷����޷����
    {
      return false;
    }
    else
    {
      a = 1;
      b = 0;
      c = -a * x_mean - b * y_mean;
    }
  }
  else
  {
    a = Dxy / den;
    b = (lambda - Dxx) / den;
    c = -a * x_mean - b * y_mean;
  }
  return true;
}

bool weightedLineFit(const std::vector<cv::Point2f> &line, double &a, double &b, double &c, double tau, int N)
{
  bool ret;
  ret = lineFit(line, a, b, c);
  if (!ret) return false;
  for (int i = 0; i < N; i++)
  {
    ret = weightedLineFitOneStep(line, a, b, c, tau);
    if (!ret) return false;
  }
  return true;
}
#else
bool weightedLineFitOneStep(const std::vector<cv::Point2f> &line, float &a, float &b, float &c, float tau)
{
  int size = line.size();
  if (size == 0)
  {
    a = 0;
    b = 0;
    c = 0;
    return false;
  }
  double x_mean = 0;
  double y_mean = 0;
  weightedMean_xy(line, x_mean, y_mean, tau, a, b, c);
  double Dxx = 0, Dxy = 0, Dyy = 0;
  weightedDxxxyyy(line, x_mean, y_mean, Dxx, Dxy, Dyy, tau, a, b, c);

  double lambda = ((Dxx + Dyy) - sqrt((Dxx - Dyy) * (Dxx - Dyy) + 4 * Dxy * Dxy)) / 2.0;
  double den = sqrt(Dxy * Dxy + (lambda - Dxx) * (lambda - Dxx));

  if (fabs(den) < 1e-5)
  {
    if (fabs(Dxx / Dyy - 1) < 1e-5) //��ʱû��һ�������ֱ�߷����޷����
    {
      return false;
    }
    else
    {
      a = 1;
      b = 0;
      c = -a * x_mean - b * y_mean;
    }
  }
  else
  {
    a = Dxy / den;
    b = (lambda - Dxx) / den;
    c = -a * x_mean - b * y_mean;
  }
  return true;
}

bool weightedLineFit(const std::vector<cv::Point2f> &line, float &a, float &b, float &c, float tau, int N)
{
  bool ret = true;
  cv::Vec4f lineFit;

  if (line.size() == 0)
    return false;

  cv::fitLine(line, lineFit, 7, 0, 1e-2, 1e-2);
  a = lineFit[1];
  b = -lineFit[0];
  c = lineFit[0] * lineFit[3] - lineFit[1] * lineFit[2];

  //if (!ret) return false;
  for (int i = 0; i < N; i++)
  {
    double a1 = a, b1 = b, c1 = c;
    ret = weightedLineFitOneStep(line, a, b, c, tau);
    if (std::abs(a1 - a) < std::numeric_limits<float>::epsilon() &&
        std::abs(b1 - b) < std::numeric_limits<float>::epsilon() &&
        std::abs(c1 - c) < std::numeric_limits<float>::epsilon())
      break;

    if (!ret) return false;
  }
  return true;
}
#endif
//
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
    if (_widthRoi < 3)
      _widthRoi = 3;
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
    // ��һ�б�ʾ���лᱻƽ���Ĵ����������������ߵ�������
    _rowIndex = cv::Mat::zeros(_heightRoi, _segmentCount + 1, CV_16UC1);
    // ��һ�б�ʾOK��ֵ�ĸ����������Ƿ�ֵ����������
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

    // ������������Ĳ�ֵ��
    _matrix = cv::getRotationMatrix2D(_roi.center, -_roi.angle, 1.0);
    for (int row = 0; row < _heightRoi; ++row)
    {
      for (int col = 0; col < _widthRoi; ++col)
      {
        cv::Point2f pt = rotate(_leftRoi + col, _topRoi + row, _matrix);
        _pos.ptr<cv::Vec2f>(row)[col][0] = pt.x;
        _pos.ptr<cv::Vec2f>(row)[col][1] = pt.y;
      }
    }
    _centerRoi = _roi.center;
    _rightMidRoi = rotate(_leftRoi + _widthRoi - 1, _topRoi + _heightRoi / 2., _matrix);

    _indexForPeakCheck = new int[_widthRoi * 2];//std::make_unique<int>(_widthRoi * 2);
    for (int i = 0; i < _widthRoi; ++i)
    {
      _indexForPeakCheck[i] = i;
    }
    for (int i = _widthRoi; i < _widthRoi * 2; ++i)
    {
      _indexForPeakCheck[i] = _widthRoi * 2 - i - 1;
    }
  }

  void process(const cv::Mat& src)
  {
#ifndef NDEBUG
    dst = src.clone();
    cv::cvtColor(dst, dst, cv::COLOR_GRAY2BGRA);
    {
      cv::Point2f pts[4];
      _roi.points(pts); // bottomLeft, topLeft, topRight, bottomRight.
      cv::line(dst, pts[0], pts[1], cv::Scalar(0, 0, 255, 128), 5);
      cv::line(dst, pts[1], pts[2], cv::Scalar(0, 0, 255, 128), 5);
      cv::line(dst, pts[2], pts[3], cv::Scalar(0, 0, 255, 128), 5);
      cv::line(dst, pts[3], pts[0], cv::Scalar(0, 0, 255, 128), 5);
    }
    cv::arrowedLine(dst, _centerRoi, _rightMidRoi, cv::Scalar(0, 0, 255, 128), 5);
#endif // !NDEBUG

    _v = 0;
    _mean = 0;
    _filtered = 0;
    _derivative = 0;
    _peakIndex = 0;

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
          // ˫���Բ�ֵ
          double Q11 = src.ptr<uchar>(y1)[x1];
          double Q12 = src.ptr<uchar>(y2)[x1];
          double Q21 = src.ptr<uchar>(y1)[x2];
          double Q22 = src.ptr<uchar>(y2)[x2];

          double x_y1 = (x2 - x) / (x2 - x1) * Q11 + (x - x1) / (x2 - x1) * Q21;
          double x_y2 = (x2 - x) / (x2 - x1) * Q12 + (x - x1) / (x2 - x1) * Q22;
          double x_y = (y2 - y) / (y2 - y1) * x_y1 + (y - y1) / (y2 - y1) * x_y2;

          // ��ֵ�ӵ���ֵ��
          for (int i = 1; i <= _rowIndex.ptr<ushort>(row)[0]; ++i)
          {
            int r = _rowIndex.ptr<ushort>(row)[i];
            _mean.ptr<float>(r)[col] += x_y;
          }

          _v.ptr<float>(row)[col] = x_y;

          int n = (row - _startOffset - _segmentWidth + 1) / _step;
          int m = (row - _startOffset - _segmentWidth + 1) % _step;
          // �߶ο�ȵ����һ�У�ȡ��ֵ
          if (m == 0 && n >= 0)
          {
            int r = _startOffset + _step * n + _segmentWidth / 2;
            _mean.ptr<float>(r)[col] /= _segmentWidth;

            // �˲�
            int c = col - _filterSize + 1 + _filterSize / 2;
            // ��Ҫ�˲�
            if (_filterSize > 1)
            {
              // �����˲�
              if (col >= _filterSize - 1)
              {
                float mean = 0;
                for (int i = 0; i < _filterSize; ++i)
                {
                  int cc = col - _filterSize + i + 1;
                  mean += _mean.ptr<float>(r)[cc] * _gaussianKernel.ptr<float>(i)[0];
                }
                _filtered.ptr<float>(r)[c] = mean;

                // ��
                if (c > _filterSize / 2 + 1 && c + 1 < _widthRoi)
                {
                  _derivative.ptr<float>(r)[c - 1] = _filtered.ptr<float>(r)[c - 2] - _filtered.ptr<float>(r)[c];
                }
              }

              // ��β��û���˲���ֱ��ʹ��ԭ����
              // TODO: ����border, border_size = _filterSize / 2
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
            // ���˲���
            else
            {
              _filtered.ptr<float>(r)[c] = _mean.ptr<float>(r)[c];

              // ��
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

    // ������
    for (int n = 0; n < _segmentCount; ++n)
    {
      int row = _startOffset + _step * n + _segmentWidth / 2;
      for (int i = 1; i < _widthRoi - 1; ++i)
      {
        int col = _indexForPeakCheck[i + _widthRoi * _traceDirection];
        float v = _derivative.ptr<float>(row)[col];
        float v_prev = _derivative.ptr<float>(row)[col - 1];
        float v_next = _derivative.ptr<float>(row)[col + 1];

        if (_transitionDirection == 0 && v < -_threshold * (1 - 5 / 100.0) && v <= v_prev && v <= v_next || // ������������Ϊ����
            _transitionDirection != 0 && v > +_threshold * (1 - 5 / 100.0) && v >= v_prev && v >= v_next)   // ������������Ϊ����
        {
          //////////////////////////////////////////////////////////////////////////
          // ������������ߣ����㶥�㣬��Ϊ��ֵ��
          double x1 = col - 1;
          double x2 = col;
          double x3 = col + 1;
          double y1 = v_prev;
          double y2 = v;
          double y3 = v_next;
          double x0;
          double y0;

          // ������ͬ���Ե�һ��Ϊ��ֵ��
          if (y2 == y1 && y2 == y3)
          {
            x0 = x1;
            y0 = y1;
          }
          else
          {
            /* oo
                 o */
            if (y2 == y1)   y1 = y3;
            /*  oo
               o   */
            if (y2 == y3)   y3 = y1;

            /*
              (1 * (y3 - y1) + 2 * (y1 - y2)) = 0
              y3 - y1 + 2y1 - 2y2 = 0
              y1 - 2y2 + y3 = 0
              y1 + y3 = 2y2
              y2 >= y1
              y2 >= y3
              ���ÿ���aΪ0���������Ϊ�����ܳ���
            */
            double a = -((x1 - x2) * (y3 - y1) - (x3 - x1) * (y1 - y2)) / ((x1 - x2) * (x2 - x3) * (x3 - x1));
            double b = (y1 - y2 - a * (x1 * x1 - x2 * x2)) / (x1 - x2);
            double c = y1 - a * x1 * x1 - b * x1;
            x0 = -b / (2 * a);
            y0 = (4 * a * c - b * b) / (4 * a);
          }
          //////////////////////////////////////////////////////////////////////////
          if (std::abs(y0) >= std::abs(_threshold))
          {
            _peakIndex.ptr<cv::Vec3f>(row)[0][0] += 1;
            int i = (int)(_peakIndex.ptr<cv::Vec3f>(row)[0][0] + 0.5);

            cv::Point2f pt = rotate(_leftRoi + x0, _topRoi + row, _matrix);
            _peakIndex.ptr<cv::Vec3f>(row)[i][0] = pt.x;
            _peakIndex.ptr<cv::Vec3f>(row)[i][1] = pt.y;
            _peakIndex.ptr<cv::Vec3f>(row)[i][2] = y0;

#ifndef NDEBUG
            cv::drawMarker(dst, pt, cv::Scalar(255, 0, 0, 128), cv::MARKER_TILTED_CROSS, 5, 3);
#endif // !NDEBUG
          }
          //////////////////////////////////////////////////////////////////////////
        }
      }
    }

    std::vector<cv::Point2f> pts;
    for (int row = 0; row < _peakIndex.rows; ++row)
    {
      int n = (int)(_peakIndex.ptr<cv::Vec3f>(row)[0][0] + 0.5);
      if (n > 0)
      {
        float x = _peakIndex.ptr<cv::Vec3f>(row)[1][0];
        float y = _peakIndex.ptr<cv::Vec3f>(row)[1][1];
        pts.push_back(cv::Point2f(x, y));
      }
    }
    /*
    //�ο�https://blog.csdn.net/liyuanbhu/article/details/50866802
    cv::Vec4f lineFit;
    //cv::fitLine(pts, lineFit, 1, 0, 1e-2, 1e-2);
    //cv::fitLine(pts, lineFit, 2, 0, 1e-2, 1e-2);
    //cv::fitLine(pts, lineFit, 3, 0, 1e-2, 1e-2);
    //cv::fitLine(pts, lineFit, 4, 0, 1e-2, 1e-2);
    //cv::fitLine(pts, lineFit, 5, 0, 1e-2, 1e-2);
    //cv::fitLine(pts, lineFit, 6, 0, 1e-2, 1e-2);
    cv::fitLine(pts, lineFit, 7, 0, 1e-2, 1e-2);
    {
      float a = lineFit[1];
      float b = -lineFit[0];
      float c = lineFit[0] * lineFit[3] - lineFit[1] * lineFit[2];
      // ax + by + c = 0
      float y1 = 0;
      float x1 = (-c - b * y1) / a;
      float y2 = src.rows - 1;
      float x2 = (-c - b * y2) / a;
#ifndef NDEBUG
      cv::line(dst, cv::Point2f(x1, y1), cv::Point2f(x2, y2), cv::Scalar(255, 0, 0, 128));
#endif // !NDEBUG
    }

    {
      double a, b, c;
      ::lineFit(pts, a, b, c);
      float y1 = 0;
      float x1 = (-c - b * y1) / a;
      float y2 = src.rows - 1;
      float x2 = (-c - b * y2) / a;
#ifndef NDEBUG
      cv::line(dst, cv::Point2f(x1, y1), cv::Point2f(x2, y2), cv::Scalar(0, 255, 0, 128));
#endif // !NDEBUG
    }
    */
    {
      float a, b, c;
      weightedLineFit(pts, a, b, c, 3, 100);
      float y1 = 0;
      float x1 = (-c - b * y1) / a;
      float y2 = src.rows - 1;
      float x2 = (-c - b * y2) / a;
#ifndef NDEBUG
      cv::line(dst, cv::Point2f(x1, y1), cv::Point2f(x2, y2), cv::Scalar(0, 255, 0, 128), 3);
      _a = a;
      _b = b;
      _c = c;
#endif // !NDEBUG
    }
#ifndef NDEBUG
    //cv::imwrite("result.bmp", dst);
#endif // !NDEBUG
  }

protected:
  // ���
  int _widthImage;
  // �߶�
  int _heightImage;
  // ����Ȥ�������� + �� + �� + �Ƕ�
  cv::RotatedRect _roi;
  int _widthRoi;
  int _heightRoi;
  float _leftRoi;
  float _topRoi;
  cv::Point2f _rightMidRoi;
  cv::Point2f _centerRoi;
  // ���ҷ���: 0 - ROI�Ƕ�ͬ����; 1 - ROI�Ƕȷ�����
  int _traceDirection;
  // ��Ե����: 0 - ������; 1 - ������
  int _transitionDirection;
  // ��ֱ�ڲ��ҷ���Ŀ�ȣ�����ƽ�������ظ���
  int _segmentWidth;
  // ��ʼƫ����
  int _startOffset;
  // �����߶μ��
  int _step;
  // �����߶ε�����
  int _segmentCount;
  // ����߶�����
  int _segmentCountMax;
  // ��Եǿ����ֵ
  float _threshold;
  // ��˹�˲��˴�С
  int _filterSize;
  // ��˹�˲�������
  float _filterSigma;
  // ��˹�˲���
  cv::Mat _gaussianKernel;
  // Ϊ������ԣ�ʹ��cv::Mat��Ϊ���ݽṹ������ʱ��ʹ��Image Watch�۲����ֵ
  // �Ӳ��ҷ����x����
  //float* _x;
  // �Ӳ��ҷ����y����
  //float* _y;
  cv::Mat _pos;
  // �Ӳ��ҷ���˫���Բ�ֵ���ֵ
  //float* _v;
  cv::Mat _v;
  // �Ӵ�ֱ����ȡƽ�����ֵ
  //float* _mean;
  cv::Mat _mean;
  //
  cv::Mat _filtered;
  // �Ӳ��ҷ�������󵼺��ֵ
  //float* _derivative;
  cv::Mat _derivative;
  // �����߶ε���������
  //int* _rowIndex;
  cv::Mat _rowIndex;
  // 
  cv::Mat _peakIndex;
  // TODO: ���ӱ�Ե�жȣ��ٷֱȣ�����ֵС�������߶������ֵ��
  int edgeSense = 5;
  //
  cv::Mat _matrix;
  //
  /*std::unique_ptr<int>*/int* _indexForPeakCheck;

public:
  cv::Mat dst;
  float _a;
  float _b;
  float _c;

};

cv::Mat func(cv::Mat& src,                 /* ����ͼ�� */
             const cv::RotatedRect& rect,  /* ROI���� */
             bool reverse,                 /* �Ƿ�˳��ROI�Ƕ� */
             bool w2b,                     /* �׵��� */
             float segmentWidth,           /* �����ߵĿ� */
             float movement,               /* �����߼�� */
             float offset,                  /* ��ʼƫ���� */
             float threshold                /* ��Ե��ֵ*/
)
{
  // ����һ�����߽����˷�����ת������ROI�����ĺ���
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
    �м䣺offset + segmentWidth / 2 + movement * n
    ��ʼ��offset + movement * n
    ��ֹ��offset + movement * n + segmentWidth - 1
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

  // �洢ɨ�����ϵ�������˫���Բ�ֵ������Ľ��
  cv::Mat line = cv::Mat::zeros(rect.size, CV_32FC4);
  // ��ֵ���������ROIͼ��
  cv::Mat lineImage = cv::Mat::zeros(rect.size, CV_32FC1);
  // ɨ���ߺ���ȡ��ֵ���ͼ��
  cv::Mat line_average = cv::Mat::zeros(segmentCnt, width, CV_32FC1);
  // ɨ���������˲����ͼ��
  cv::Mat line_blur = cv::Mat::zeros(segmentCnt, width, CV_32FC1);
  // �󵼺��ͼ��
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

  // ����ƽ��
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

  // ����ƽ��
  const int kernelSize = 3; // �������segment�ĳ���
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

  // ��
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

  // TODO: ���� y Ҳ��Ҫ����λ��
  // TODO: �ҳ�����Ҫ��ĵ��λ��
  // TODO: �����������ֵλ��
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

  for (int i = 0; i < 360; ++i)
  {
    LineEdgeDectector d;
    cv::RotatedRect roi(cv::Point2f(1840, 1130/*1416, 784*/), cv::Size2f(800, 800), i);

    tm.reset();
    tm.start();
    d.init(src.cols, src.rows, roi, 1, 0, 3, 0, 3, -1, 50, 3, 0.8);
    tm.stop();
    ms = tm.getTimeMilli();
    qDebug() << i << ": LineEdgeDectector::init " << ms << " ms";

    tm.reset();
    tm.start();
    //*cv::Mat m = */func(src, cv::RotatedRect(cv::Point2f(1840, 1130), cv::Size2f(800, 800), 5/*i*/), true, true, 3, 5, 0, 40.f);
    d.process(src);
    tm.stop();
    ms = tm.getTimeMilli();
    qDebug() << i << ": LineEdgeDectector::process " << ms << " ms" << ", a = " << d._a << ", b = " << d._b << ", c" << d._c;

    std::stringstream ss;
    ss << i << ".bmp";
    cv::imwrite(ss.str(), d.dst);
  }
}
