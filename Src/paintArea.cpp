#include "enums.h"
#include "paintArea.h"

PaintArea::PaintArea(QWidget *parent, QString file) : QWidget(parent) {
  qDebug() << "PaintArea::PaintArea(void)";
  _startPoint = _endPoint = QPoint(0,0);
  if(file!=""){
    _buffer = new QPixmap(file);
    parent->setFixedWidth(_buffer->width());
    parent->setFixedHeight(_buffer->height());
  }else{
    _buffer = new QPixmap(parent->size());
    _buffer->fill(Qt::white);
  }
  _release=false;
}

void PaintArea::mousePressEvent(QMouseEvent* evt) {
  qDebug() << "PaintArea::mousePressEvent(void)";
  _release=false;
  _startPoint = _endPoint = evt->pos(); 
}

void PaintArea::mouseMoveEvent(QMouseEvent* evt) 
{
// qDebug() << "PaintArea::mouseMoveEvent(void)";
  _endPoint = evt->pos(); 
  update();
}
void PaintArea::mouseReleaseEvent(QMouseEvent* evt) 
{
  qDebug() << "PaintArea::mouseReleaseEvent(void)";
  _release=true;
  update();

}

void PaintArea::mouseDoubleClickEvent (QMouseEvent* evt) {
  qDebug() << "PaintArea::mouseDoubleClickEvent(void)";
}

void PaintArea::paintEvent(QPaintEvent* evt) 
{
  qDebug() << "PaintArea::paintEvent(void)";
  qDebug() << _currentTool;
  QPainter paintWindow(this);
  QPainter paintBuffer(_buffer);
  paintWindow.drawPixmap(0,0, *_buffer);
  switch(_currentTool) {
    case TOOLS_ID_FREEHAND :
      paintBuffer.drawPoint(_endPoint);
      paintWindow.drawPoint(_endPoint);
      break;
    case TOOLS_ID_LINE :
      if (_release) paintBuffer.drawLine(_startPoint,_endPoint);
      paintWindow.drawLine(_startPoint,_endPoint);
      break;
    case TOOLS_ID_RECTANGLE :
      if (_release) paintBuffer.drawRect(QRect(_startPoint,_endPoint));
      paintWindow.drawRect(QRect(_startPoint,_endPoint));
      break;
  case TOOLS_ID_CIRCLE:
    if(_release)paintBuffer.drawEllipse(_startPoint, abs(_endPoint.x()-_startPoint.x()),abs(_endPoint.y()-_startPoint.y()));
    paintWindow.drawEllipse(_startPoint, abs(_endPoint.x()-_startPoint.x()),abs(_endPoint.y()-_startPoint.y()));
    default :
      break;
  }
}

void PaintArea::setCurrentTool(int tool) {
  _currentTool = tool;
}

/**
 * loadPicture
 *load a picture
 * @param filename: path 
 **/
bool PaintArea::loadPicture(QString filename){
  bool load = _buffer->load(filename);
  if(load)
    {

    }
  update();
  return load;
}


/**
 * savePicture
 * save the actual picture
 * @param filename: path to save picture
 **/
bool PaintArea::savePicture(QString filename){
  return _buffer->save(filename);
}
