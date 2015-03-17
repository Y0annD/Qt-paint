#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QActionGroup>
#include <QIcon>
#include <QMessageBox>
#include <QScrollArea>
#include <QSignalMapper>
#include <QFileDialog>
#include <QColorDialog>

#include <QDebug>
#include <QDate>

#include "paintArea.h"

class PaintWindow : public QMainWindow
{
  Q_OBJECT  
  public:
    PaintWindow(QWidget *parent = 0);
  signals:
   void toolMapped(int digit);
  public slots :
    void quit(void);
    void _exit(void);
    void draw(void);
  private slots :
    /* Menu file*/
    void _newFile(void);
    void _openFile(void);
    void _saveFile(void);
    void _saveAsFile(void);
    void color(void);

    /* About menu*/
    void _about(void);
    void _aboutQt(void);

  private :
   void _createMenus(void);
   void _createToolBars(void);
   void _createActions(void);
   void _connectActions(void);
   void _connectSignals(void);

   // client
   PaintArea *_area;
   // menus
   QToolBar *_toolBar;
   QMenu *_fileMenu, *_toolMenu, *_styleMenu, *_helpMenu ;
   QMenu *_penSubMenu, *_linePenSubMenu, *_widthPenSubMenu, *_brushSubMenu, *_fillBrushSubMenu;
   // actions
   QAction *_newAct,*_openAct, *_saveAct, *_saveAsAct, *_exitAct, *_aboutAct, *_aboutQtAct;
   QActionGroup *_toolsQag;
   QAction *_freehandAct, *_lineAct, *_rectAct, *_polyAct, *_textAct, *_circleAct;
   QAction *_colorPen, *_colorBrush, *_fontAct;
   // mapping 
   QSignalMapper *_signalMapper;

   // filename
   QString filename;
};
#endif

