#ifndef _IMAGE_WINDOW_H_
#define _IMAGE_WINDOW_H_

#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QPainter> 

namespace sv {

class QRotatedRectF
{
public:
  QRotatedRectF()
  {}

  QRotatedRectF(qreal x, qreal y, qreal width, qreal height, qreal theta)
    : xp(x)
    , yp(y)
    , w(width)
    , h(height)
    , t(theta)
  {}

  QRotatedRectF(const QPointF& center, const QSize& size, qreal theta)
    : xp(center.x())
    , yp(center.y())
    , w(size.width())
    , h(size.height())
    , t(theta)
  {
    _matrix.translate(xp, yp);
    _matrix.rotate(t);
  }

  QPointF topLeft    () const { return _matrix.map(shadowTopLeft    ()); }
  QPointF bottomRight() const { return _matrix.map(shadowBottomRight()); }
  QPointF topRight   () const { return _matrix.map(shadowTopRight   ()); }
  QPointF bottomLeft () const { return _matrix.map(shadowBottomLeft ()); }

  QPointF center() const { return _matrix.map(shadowTopLeft()); }

protected:
  QPointF shadowTopLeft    () const { return QPointF(center() + QPointF(-w / 2, -h / 2)); }
  QPointF shadowBottomRight() const { return QPointF(center() + QPointF(+w / 2, +h / 2)); }
  QPointF shadowTopRight   () const { return QPointF(center() + QPointF(+w / 2, -h / 2)); }
  QPointF shadowBottomLeft () const { return QPointF(center() + QPointF(-w / 2, +h / 2)); }


private:
  qreal xp;
  qreal yp;
  qreal w;
  qreal h;
  qreal t;
  QMatrix _matrix;
};

class ImageWindow : public QWidget
{
  Q_OBJECT

public:
  ImageWindow(QWidget* parent = nullptr) : QWidget(parent)
  { }

  void setImage(const QImage& i)
  {
    _canvas = i.copy();
    setFixedSize(_canvas.size() * _scale);
  }

  void setPoints(const QVector<QPointF> pts)
  {
    _points = pts;
  }

  void setLine(const QLineF& line)
  {
    _line = line;
  }

protected:
  virtual void paintEvent(QPaintEvent *event)
  {
    QPainter painter(this);

    drawImage(painter);
    drawRoi(painter);
    drawLine(painter);
    drawPoints(painter);
  }

  void drawImage(QPainter& painter)
  {
    painter.save();

    qreal s = /*1 /*/ _scale;
    painter.scale(s, s);
    painter.drawImage(0, 0, _canvas);

    painter.restore();
  }

  void drawPoints(QPainter& painter)
  {
    painter.save();

    qreal s = /*1 /*/ _scale;
    painter.scale(s, s);

    painter.setPen(QPen(QColor(255, 215, 0), 2 / _scale));

    for (auto& pt : _points)
    {
      painter.save();

      painter.translate(pt);
      painter.rotate(45);

      qreal size = _crossSize / s;

      painter.drawLine(QPointF(-size / 2, 0), QPointF(size / 2, 0));
      painter.drawLine(QPointF(0, -size / 2), QPointF(0, size / 2));

      painter.restore();
    }

    painter.restore();
  }

  void drawLine(QPainter& painter)
  {
    painter.save();

    qreal s = /*1 /*/ _scale;
    painter.scale(s, s);

    painter.setPen(QPen(Qt::green, 0));

    painter.drawLine(_line);

    painter.restore();
  }

  void drawRoi(QPainter& painter)
  {}

private:
  QImage _canvas;
  QVector<QPointF> _points;
  QLineF _line;
  QRotatedRectF _roi;

  qreal _crossSize = 20;
  qreal _scale = 25;
};

}

#endif
