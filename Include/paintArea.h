#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPainter>
#include<QVector>
#include <QDebug>
#include <math.h>

class PaintArea : public QWidget
{
  Q_OBJECT  

  public:
  PaintArea(QWidget *parent = 0, QString file = "");
  bool savePicture(QString);
  bool loadPicture(QString);
  void reset(QWidget*);
  public slots:
    void setCurrentTool(int);

  protected :
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent* evt);
    void paintEvent(QPaintEvent*);
   

  private :
   QPoint  _startPoint,_endPoint;
   QPolygon polygon;
   QPixmap *_buffer;
   // scene ou sera affiché les éléments
   QGraphicsScene scene;
   int _currentTool;
   bool _release, editPoly;
   QVector<QPoint> points;
};
#endif

