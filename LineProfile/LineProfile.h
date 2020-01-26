#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LineProfile.h"

namespace sv {
class ImageWindow;
}

class LineProfile : public QMainWindow
{
  Q_OBJECT

public:
  LineProfile(QWidget *parent = Q_NULLPTR);

protected slots:
  void TrendDirectionChanged();
  void ScanDirectionChanged();
  void EdgeDirectionChanged();
  void SpecifiedEdgeChanged();
  void EdgeSensitivityChanged();
  void EdgeFilterWidthChanged();
  void EdgeIntensityUpperLimitChanged();
  void EdgeIntensityLowerLimtiChanged();
  void SegmentSizeChanged();
  void SegmentShiftChanged();
  void SegmentOffsetChanged();
  void PrimaryTargetChanged();
  void PrimaryTargetSpecifiedChanged();
  void MaxNoSegmentsChanged();

private:
  Ui::LineProfileClass ui;

  sv::ImageWindow* _imageWindow = nullptr;
};
