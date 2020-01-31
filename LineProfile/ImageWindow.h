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
  {
    createMatrix(xp, yp, t);
  }

  QRotatedRectF(const QPointF& center, const QSize& size, qreal theta)
    : xp(center.x())
    , yp(center.y())
    , w(size.width())
    , h(size.height())
    , t(theta)
  {
    createMatrix(xp, yp, t);
  }

  QPointF topLeft    () const { return _matrix.map(shadowTopLeft    ()); }
  QPointF bottomRight() const { return _matrix.map(shadowBottomRight()); }
  QPointF topRight   () const { return _matrix.map(shadowTopRight   ()); }
  QPointF bottomLeft () const { return _matrix.map(shadowBottomLeft ()); }

  QPointF center() const { return QPointF(xp, yp); }

protected:
  QPointF shadowTopLeft    () const { return QPointF(center() + QPointF(-w / 2, -h / 2)); }
  QPointF shadowBottomRight() const { return QPointF(center() + QPointF(+w / 2, +h / 2)); }
  QPointF shadowTopRight   () const { return QPointF(center() + QPointF(+w / 2, -h / 2)); }
  QPointF shadowBottomLeft () const { return QPointF(center() + QPointF(-w / 2, +h / 2)); }

  void createMatrix(qreal x, qreal y, qreal t)
  {
    double a = qCos(qDegreesToRadians(t));
    double b = -qSin(qDegreesToRadians(t));
    double m11 = a;
    double m12 = -b;
    double m21 = b;
    double m22 = a;
    double m31 = (1 - a) * x - b * y;
    double m32 = b * x + (1 - a) * y;
    _matrix.setMatrix(m11, m12, m21, m22, m31, m32);
  }
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

  void setPoints(const QList<QPointF> pts)
  {
    _points = pts;
  }

  void setLine(const QLineF& line)
  {
    _line = line;
  }

  void setRoi(const QRotatedRectF& rect)
  {
    _roi = rect;
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

    painter.setPen(QPen(QColor(255, 215, 0), 0/*2 / _scale*/));
    painter.setBrush(QBrush(QColor(255, 215, 0)));
    /* draw cross
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
  */

    for (int i = 0; i < _points.size(); i++)
    {
      painter.save();

      QPointF pt = _points[i];
      qreal size = _crossSize / s;

      painter.setRenderHint(QPainter::Antialiasing);
      painter.drawEllipse(pt, size, size);
      painter.restore();

      if (i > 0)
      {
        QPointF pt1 = _points[i - 1];
        painter.drawLine(pt, pt1);
      }

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
  {
    painter.save();

    qreal s = /*1 /*/ _scale;
    painter.scale(s, s);

    painter.setPen(QPen(Qt::blue, 0));

    QPolygonF polygon;
    polygon << _roi.bottomLeft() << _roi.topLeft() << _roi.topRight() << _roi.bottomRight();
    painter.drawPolygon(polygon, Qt::OddEvenFill);

    painter.drawLine(_roi.center(), (_roi.bottomRight() + _roi.topRight()) / 2);

    painter.restore();
}

private:
  QImage _canvas;
  QList<QPointF> _points;
  QLineF _line;
  QRotatedRectF _roi;

  qreal _crossSize = 2;
  qreal _scale = 25;
};

}

#endif
