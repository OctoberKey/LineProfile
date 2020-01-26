#pragma once

#ifndef _PROFILE_POSITION_H_
#define _PROFILE_POSITION_H_

#include <opencv2/opencv.hpp>

namespace sv {

enum TrendDirection_
{
  TD_TOP_TO_BOTTOM, TD_BOTTOM_TO_TOP, TD_LEFT_TO_RIGHT, TD_RIGHT_TO_LEFT
};

enum ScanDirection_
{
  SD_FORWARD, SD_REVERSE
};

enum EdgeDirection_
{
  ED_LIGHT_TO_DARK, ED_DARK_TO_LIGHT, ED_BOTH
};

template<typename _Tp> struct Range_
{
  _Tp UpperLimit;
  _Tp LowerLimit;
};

typedef Range_<int> Rangei;
typedef Range_<__int64> Rangel;
typedef Range_<float> Rangef;
typedef Range_<double> Ranged;
typedef Rangei Range;

enum PrimaryTarget_
{
  PT_MAX, PT_MIN, PT_SPECIFIED
};

struct EdgeDetectionConfig
{
  int     TrendDirection;
  int     ScanDirection;
  int     EdgeDirection;
  int     SpecifiedEdge;

  int     EdgeSensitivity;
  int     EdgeFilterWidth;
  Rangef  EdgeIntensity;

  int     SegmentSize;
  int     SegmentShift;
  int     SegmentOffset;
  int     PrimaryTarget;
};

class ProfilePosition
{
public:
  ProfilePosition() {}

  ProfilePosition(const EdgeDetectionConfig& config)
  {
    Initialize(config);
  }

  void Initialize(const EdgeDetectionConfig& config)
  {
    _config = config;
  }

  void Process(const void* data)
  {
    ;
  }

private:
  cv::Size _imgSize;

  cv::RotatedRect _roiRect;

  cv::RotatedRect _roiRectCor;

  EdgeDetectionConfig _config;
};

}

#endif
