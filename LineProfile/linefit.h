#pragma once

#ifndef _LINE_FIT_H_
#define _LINE_FIT_H_

#include <math.h>

namespace sv {

//#define USE_MY

static const double eps = 1e-6;

//! Distance types for Distance Transform and M-estimators
//! @see distanceTransform, fitLine
enum DistanceTypes {
  DIST_USER = -1,  //!< User defined distance
  DIST_L1 = 1,   //!< distance = |x1-x2| + |y1-y2|
  DIST_L2 = 2,   //!< the simple euclidean distance
  DIST_C = 3,   //!< distance = max(|x1-x2|,|y1-y2|)
  DIST_L12 = 4,   //!< L1-L2 metric: distance = 2(sqrt(1+x*x/2) - 1))
  DIST_FAIR = 5,   //!< distance = c^2(|x|/c-log(1+|x|/c)), c = 1.3998
  DIST_WELSCH = 6,   //!< distance = c^2/2(1-exp(-(x/c)^2)), c = 2.9846
  DIST_HUBER = 7,   //!< distance = |x|<c ? x^2/2 : c(|x|-c/2), c=1.345
  DIST_TUKEY = 8    //!< distance = |x|<c ? x^2/2 : c(|x|-c/2), c=1.345
};

static inline int sqr(int x) { return x * x; }
static inline float sqr(float x) { return x * x; }
static inline double sqr(double x) { return x * x; }

static void weightL1(float *d, int count, float *w)
{
  int i;

  for (i = 0; i < count; i++)
  {
    double t = fabs((double)d[i]);
    w[i] = (float)(1. / MAX(t, eps));
  }
}

static void weightL12(float *d, int count, float *w)
{
  int i;

  for (i = 0; i < count; i++)
  {
    w[i] = 1.0f / (float)std::sqrt(1 + (double)(d[i] * d[i] * 0.5));
  }
}

static void weightHuber(float *d, int count, float *w, float _c)
{
  int i;
  const float c = _c <= 0 ? 1.345f : _c;

  for (i = 0; i < count; i++)
  {
    if (d[i] < c)
      w[i] = 1.0f;
    else
      w[i] = c / d[i];
  }
}

static void weightFair(float *d, int count, float *w, float _c)
{
  int i;
  const float c = _c == 0 ? 1 / 1.3998f : 1 / _c;

  for (i = 0; i < count; i++)
  {
    w[i] = 1 / (1 + d[i] * c);
  }
}

static void weightWelsch(float *d, int count, float *w, float _c)
{
  int i;
  const float c = _c == 0 ? 1 / 2.9846f : 1 / _c;

  for (i = 0; i < count; i++)
  {
    w[i] = (float)std::exp(-d[i] * d[i] * c * c);
  }
}

static void weightTukey(float *d, int count, float *w, float _c)
{
  int i;
  const float c = _c == 0 ? 1.f : _c;

  for (i = 0; i < count; i++)
  {
    if (d[i] < c)
      w[i] = sqr(1 - sqr(d[i] / c));
    else
      w[i] = 0;
  }
}

static double calcDist2D(const cv::Point2f* points, int count, float *_line, float *dist)
{
  int j;
  float px = _line[2], py = _line[3];
  float nx = _line[1], ny = -_line[0];
  double sum_dist = 0.;

  for (j = 0; j < count; j++)
  {
    float x, y;

    x = points[j].x - px;
    y = points[j].y - py;

    dist[j] = (float)fabs(nx * x + ny * y);
    sum_dist += dist[j];
  }

  return sum_dist;
}

static void fitLine2D_wods(const cv::Point2f* points, int count, float *weights, float *line)
{
  CV_Assert(count > 0);
  double x = 0, y = 0, x2 = 0, y2 = 0, xy = 0, w = 0;
  double dx2, dy2, dxy;
  int i;
  float t;

  // Calculating the average of x and y...
  if (weights == 0)
  {
    for (i = 0; i < count; i += 1)
    {
      x += points[i].x;
      y += points[i].y;
      x2 += points[i].x * points[i].x;
      y2 += points[i].y * points[i].y;
      xy += points[i].x * points[i].y;
    }
    w = (float)count;
  }
  else
  {
    for (i = 0; i < count; i += 1)
    {
      x += weights[i] * points[i].x;
      y += weights[i] * points[i].y;
      x2 += weights[i] * points[i].x * points[i].x;
      y2 += weights[i] * points[i].y * points[i].y;
      xy += weights[i] * points[i].x * points[i].y;
      w += weights[i];
    }
  }

  x /= w;
  y /= w;
  x2 /= w;
  y2 /= w;
  xy /= w;

  dx2 = x2 - x * x;
  dy2 = y2 - y * y;
  dxy = xy - x * y;

  t = (float)atan2(2 * dxy, dx2 - dy2) / 2;
  // y = kx + b
  // y = sin(θ) / cos(θ) y + b
  // -sin(θ) • x + cos(θ) • y + c = 0
  //
  line[0] = (float)cos(t);
  line[1] = (float)sin(t);

  line[2] = (float)x;
  line[3] = (float)y;

  qDebug() << -t / 3.14159265358 * 180;
}

static void fitLine2D_wods1(const cv::Point2f* points, int count, float *weights, float *line)
{
  CV_Assert(count > 0);
  double ur = 0, uc = 0, urr = 0, urc = 0, ucc = 0, w = 0;
  double dx2, dy2, dxy;
  int i;
  float t;

  // Calculating the average of x and y...
  if (weights == 0)
  {
    for (i = 0; i < count; i += 1)
    {
      ur += points[i].x;
      uc += points[i].y;
    }
    w = (float)count;
  }
  else
  {
    for (i = 0; i < count; i += 1)
    {
      ur += weights[i] * points[i].x;
      uc += weights[i] * points[i].y;
      w += weights[i];
    }
  }

  ur /= w;
  uc /= w;

  if (weights == 0)
  {
    for (i = 0; i < count; i += 1)
    {
      urr += (points[i].x - ur) * (points[i].x - ur);
      urc += (points[i].x - ur) * (points[i].y - uc);
      ucc += (points[i].y - uc) * (points[i].y - uc);
    }
  }
  else
  {
    for (i = 0; i < count; i += 1)
    {
      urr += weights[i] * (points[i].x - ur) * (points[i].x - ur);
      urc += weights[i] * (points[i].x - ur) * (points[i].y - uc);
      ucc += weights[i] * (points[i].y - uc) * (points[i].y - uc);
    }
  }

  urr /= w;
  urc /= w;
  ucc /= w;

  float lamda = ((urr + ucc) - sqrt(sqr(urr - ucc) + 4 * sqr(urc))) / 2;
  float denominator = sqrt(sqr(urc) + sqr(lamda - urr));

  t = -(float)atan2(urc, lamda - urr);
  line[0] = (float)cos(t);
  line[1] = (float)sin(t);
  //line[0] = urc / denominator;
  //line[1] = (lamda - urr) / denominator;

  line[2] = (float)ur;
  line[3] = (float)uc;

  qDebug() << t / 3.14159265358 * 180;
}

/* Takes an array of 2D points, type of distance (including user-defined
 distance specified by callbacks, fills the array of four floats with line
 parameters A, B, C, D, where (A, B) is the normalized direction vector,
 (C, D) is the point that belongs to the line. */

static void fitLine2D(const cv::Point2f * points, int count, int dist,
                      float _param, float reps, float aeps, float *line)
{
  double EPS = count * FLT_EPSILON;
  void(*calc_weights) (float *, int, float *) = 0;
  void(*calc_weights_param) (float *, int, float *, float) = 0;
  int i, j, k;
  float _line[4], _lineprev[4];
  float rdelta = reps != 0 ? reps : 1.0f;
  float adelta = aeps != 0 ? aeps : 0.01f;
  double min_err = DBL_MAX, err = 0;
  cv::RNG rng((uint64)-1);

  memset(line, 0, 4 * sizeof(line[0]));

  switch (dist)
  {
  case cv::DIST_L2:
#ifdef USE_MY
    return fitLine2D_wods1(points, count, 0, line);
#else
    return fitLine2D_wods(points, count, 0, line);
#endif

  case cv::DIST_L1:
    calc_weights = weightL1;
    break;

  case cv::DIST_L12:
    calc_weights = weightL12;
    break;

  case cv::DIST_FAIR:
    calc_weights_param = weightFair;
    break;

  case cv::DIST_WELSCH:
    calc_weights_param = weightWelsch;
    break;

  case cv::DIST_HUBER:
    calc_weights_param = weightHuber;
    break;

  case sv::DIST_TUKEY:
    calc_weights_param = weightTukey;
    break;

    /*case DIST_USER:
     calc_weights = (void ( * )(float *, int, float *)) _PFP.fp;
     break;*/
  default:
    //CV_Error(CV_StsBadArg, "Unknown distance type");
    ;
  }

  cv::AutoBuffer<float> wr(count * 2);
  float *w = wr.data(), *r = w + count;

  for (k = 0; k < 20; k++)
  {
    int first = 1;
    for (i = 0; i < count; i++)
      w[i] = 0.f;

    for (i = 0; i < MIN(count, 10); )
    {
      j = rng.uniform(0, count);
      if (w[j] < FLT_EPSILON)
      {
        w[j] = 1.f;
        i++;
      }
    }

#ifdef USE_MY
    fitLine2D_wods1(points, count, w, _line);
#else
    fitLine2D_wods(points, count, w, _line);
#endif
    for (i = 0; i < 30; i++)
    {
      double sum_w = 0;

      if (first)
      {
        first = 0;
      }
      else
      {
        double t = _line[0] * _lineprev[0] + _line[1] * _lineprev[1];
        t = MAX(t, -1.);
        t = MIN(t, 1.);
        if (fabs(acos(t)) < adelta)
        {
          float x, y, d;

          x = (float)fabs(_line[2] - _lineprev[2]);
          y = (float)fabs(_line[3] - _lineprev[3]);

          d = x > y ? x : y;
          if (d < rdelta)
            break;
        }
      }
      /* calculate distances */
      err = calcDist2D(points, count, _line, r);
      if (err < EPS)
        break;

      /* calculate weights */
      if (calc_weights)
        calc_weights(r, count, w);
      else
        calc_weights_param(r, count, w, _param);

      for (j = 0; j < count; j++)
        sum_w += w[j];

      if (fabs(sum_w) > FLT_EPSILON)
      {
        sum_w = 1. / sum_w;
        for (j = 0; j < count; j++)
          w[j] = (float)(w[j] * sum_w);
      }
      else
      {
        for (j = 0; j < count; j++)
          w[j] = 1.f;
      }

      /* save the line parameters */
      memcpy(_lineprev, _line, 4 * sizeof(float));

      /* Run again... */
#ifdef USE_MY
      fitLine2D_wods1(points, count, w, _line);
#else
      fitLine2D_wods(points, count, w, _line);
#endif
    }

    if (err < min_err)
    {
      min_err = err;
      memcpy(line, _line, 4 * sizeof(line[0]));
      if (err < EPS)
        break;
    }
  }
}

void fitLine(cv::InputArray _points, cv::OutputArray _line, int distType,
             double param, double reps, double aeps)
{
  //CV_INSTRUMENT_REGION();

  cv::Mat points = _points.getMat();

  float linebuf[6] = { 0.f };
  int npoints2 = points.checkVector(2, -1, false);
  int npoints3 = points.checkVector(3, -1, false);

  CV_Assert(npoints2 >= 0 || npoints3 >= 0);

  if (points.depth() != CV_32F || !points.isContinuous())
  {
    cv::Mat temp;
    points.convertTo(temp, CV_32F);
    points = temp;
  }

  if (npoints2 >= 0)
    fitLine2D(points.ptr<cv::Point2f>(), npoints2, distType,
    (float)param, (float)reps, (float)aeps, linebuf);
  //else
  //    fitLine3D( points.ptr<cv::Point3f>(), npoints3, distType,
                 //(float)param, (float)reps, (float)aeps, linebuf);

  cv::Mat(npoints2 >= 0 ? 4 : 6, 1, CV_32F, linebuf).copyTo(_line);
}

}
#endif