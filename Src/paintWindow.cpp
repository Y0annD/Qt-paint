#include "enums.h"
#include "paintWindow.h"

//--------------------------------------------------------------------------------
PaintWindow::PaintWindow(QWidget *parent) : QMainWindow(parent) {
   qDebug() << "PaintWindow::PaintWindow(QWidget *parent)";
   qDebug() << "Date: " << QDate::currentDate();

   _createMenus();
   _createActions();
   _createToolBars();
   _connectActions();

  _area = new PaintArea(this);
   setCentralWidget(_area);

  _signalMapper = new QSignalMapper(this);
  _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
  _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
  _signalMapper->setMapping(_circleAct, TOOLS_ID_CIRCLE);
  _signalMapper->setMapping(_rectAct, TOOLS_ID_RECTANGLE);
  _signalMapper->setMapping(_polyAct, TOOLS_ID_POLYGON);

  _connectSignals();
}
//--------------------------------------------------------------------------------
void PaintWindow::_createMenus(void) {
 QMenuBar* menubar = menuBar(); 
 statusBar()->showMessage("Ready");
 _fileMenu = menubar->addMenu( tr("&File") );
 _toolMenu = menubar->addMenu("&Tool");
 _helpMenu = menubar->addMenu( tr("&Help") );
}
//--------------------------------------------------------------------------------
void PaintWindow::_createToolBars(void) {
  _toolBar=addToolBar( tr("File") ); 
}
//--------------------------------------------------------------------------------
void PaintWindow::_createActions(void) {

  _newAct = new QAction(QIcon(":/Images/new.png"), tr("&New..."), this);
  _newAct->setShortcut(tr("Ctrl+N"));
  _newAct->setToolTip(tr("New file tooltip"));
  _newAct->setStatusTip(tr("New file status"));
  _newAct->setData(QVariant("_newAct data"));

  _saveAct = new QAction(tr("&Save"),this);
  //  _saveAct->setDisabled(true);
  _saveAct->setIcon(QIcon(":/Images/save.png"));
  _saveAct->setShortcut(tr("Ctrl+S"));
  _saveAct->setToolTip(tr("Save file tooltip"));
  _saveAct->setStatusTip(tr("Save file status"));
  _saveAct->setData(QVariant("_saveAct data"));

  _saveAsAct = new QAction(tr("&Save As"),this);
  //  _saveAsAct->setDisabled(true);
  _saveAsAct->setIcon(QIcon(":/Images/save_as.png"));
  _saveAsAct->setShortcut(tr("Ctrl+Maj+S"));
  _saveAsAct->setToolTip(tr("Save As file tooltip"));
  _saveAsAct->setStatusTip(tr("Save Asfile status"));
  _saveAsAct->setData(QVariant("_saveAsAct data"));

  _openAct = new QAction(tr("&Open"),this);
  _openAct->setIcon(QIcon(":/Images/open.png"));
  _openAct->setShortcut(tr("Ctrl+O"));
  _openAct->setToolTip(tr("Open file tooltip"));
  _openAct->setStatusTip(tr("Open file status"));
  _openAct->setData(QVariant("_Open data"));

  _exitAct = new QAction(tr("&Exit..."), this);
  _exitAct->setShortcut(tr("Ctrl+X"));
  _exitAct->setToolTip(tr("Exit"));
  _exitAct->setStatusTip(tr("Exit"));
  _exitAct->setIcon(QIcon(":/Images/exit.png"));
  _exitAct->setData(QVariant("_quitAct data"));

  _aboutAct    = new QAction(tr("&About Us.."), this);
  _aboutQtAct    = new QAction(tr("&About Qt.."), this);

  _toolsQag = new QActionGroup( this );
  _freehandAct = new QAction(QIcon(":/Images/tool_pen.png"),tr("&Freehand"),  this);
  _lineAct = new QAction(QIcon(":/Images/tool_line.png"),tr("&Line"), this);
  _circleAct = new QAction(QIcon(":/Images/tool_ellipse.png"),tr("&Circle"),this);
  _rectAct = new QAction(QIcon(":/Images/tool_rectangle.png"),tr("&Rectangle"), this);
  _polyAct = new QAction(QIcon(":/Images/tool_polygon.png"),tr("&Polygon"), this);
  _textAct = new QAction(QIcon(":/Images/tool_text.png"),tr("&Text"),this);
  _freehandAct->setCheckable(true);
  _lineAct->setCheckable(true);
  _circleAct->setCheckable(true);
  _rectAct->setCheckable(true);
  _polyAct->setCheckable(true);
}
//--------------------------------------------------------------------------------
void PaintWindow::_connectActions(void) {
 _fileMenu->addAction(_newAct);
 _fileMenu->addSeparator();
 _fileMenu->addAction(_openAct);
 _fileMenu->addAction(_saveAct);
 _fileMenu->addAction(_saveAsAct);
 _fileMenu->addSeparator();
 _fileMenu->addAction(_exitAct);

 _toolBar->addAction(_newAct);
 _toolBar->addAction(_openAct);
 _toolBar->addAction(_saveAct);
 _toolBar->addAction(_saveAsAct);
 _toolBar->addAction(_exitAct);

 _toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_circleAct);
 _toolsQag->addAction(_rectAct);
 _toolsQag->addAction(_polyAct);


 _toolMenu->addAction(_freehandAct);
 _toolMenu->addAction(_lineAct);
 _toolMenu->addAction(_rectAct);
 _toolMenu->addAction(_circleAct);
 _toolMenu->addAction(_polyAct);
 _toolMenu->addSeparator();
 _toolMenu->addAction(_textAct);
 
 _helpMenu->addAction(_aboutAct);
 _helpMenu->addAction(_aboutQtAct);
}

//--------------------------------------------------------------------------------
void PaintWindow::_connectSignals(void) {

 connect(_newAct, SIGNAL(triggered()), this,SLOT(_newFile( )) );
 connect(_openAct, SIGNAL(triggered()), this,SLOT(_openFile( )) );
 connect(_saveAct, SIGNAL(triggered()), this,SLOT(_saveFile( )) );
 connect(_saveAsAct, SIGNAL(triggered()), this,SLOT(_saveAsFile( )) );
 connect(_exitAct,SIGNAL(activated()), this, SLOT(_exit()));

 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polyAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_circleAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_textAct, SIGNAL(activated()),_signalMapper,SLOT(map()));

 connect(_aboutAct, SIGNAL(triggered()),this, SLOT(_about()));
 connect(_aboutQtAct,SIGNAL(triggered()),this, SLOT(_aboutQt()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)) );
}
//--------------------------------------------------------------------------------
void PaintWindow::_about(void) {
 QMessageBox::information( this,"About Us","Yoann Diquélou - Leïla Toscer","Au dodo !");
}

void PaintWindow::_aboutQt(void) {
 QMessageBox::aboutQt(this);
}
//--------------------------------------------------------------------------------

/**
 * Affiche une boite de dialogue pour que l'utilisateur confirme 
 * ou non la sortie
 **/
void PaintWindow::_exit(){
QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Qt-Paint Diquélou Toscer", "Quit?",
                                QMessageBox::Yes|QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    qDebug() << "Yes was clicked";
    QApplication::quit();
  } else {
    qDebug() << "Yes was *not* clicked";
  }
}

void PaintWindow::_newFile(void)  {
  qDebug() << "PaintWindow::_newFile(void)";
  /*  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Warning);
  msgBox.setText("Le document a été modifié.");
  msgBox.setInformativeText("Voulez-vous enregistrer les changements avant de recommencer?");
  msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Save);
  int ret = msgBox.exec();*/
  
  int ret = QMessageBox::warning(this, tr("Paint Diquélou - Toscer"),
                                tr("The document has been modified.\n"
                                   "Do you want to save your changes?"),
                                QMessageBox::Save | QMessageBox::Discard
                                | QMessageBox::Cancel,
                                QMessageBox::Save);

  switch(ret){
  case QMessageBox::Save:
    // save the picture
    _saveFile();
    _area->reset(this);
    //_area = new PaintArea(this);
    break;
  case QMessageBox::Discard:
    // Don't save the picture
    _area->reset(this);
    break;
  case QMessageBox::Cancel:
    break;
  default:
    // Hey GUY you're wrong
    break;
  }
}

void PaintWindow::_openFile(void){
  qDebug() << "PaintWindow::_openFile(void)";
  QString file;
  file = QFileDialog::getOpenFileName(this,
                                          tr("Open Image"),NULL, tr("ImageFile(*.png *.jpg *.bmp)"));
  if(file!=""){
    /*_area=new PaintArea(this,file);
      setCentralWidget(_area);*/
    _area->loadPicture(file);
    _saveAct->setDisabled(false);
    _saveAsAct->setDisabled(false);
    filename = file;
  }
  
  qDebug() << filename;
}

void PaintWindow::_saveFile(void){
  qDebug() << "PaintWindow::_saveFile(void)";
  if(filename != NULL && filename != ""){
    _area->savePicture(filename);
  }else{
    _saveAsFile();
  }
}

void PaintWindow::_saveAsFile(void){
  qDebug() << "PaintWindow::_saveAsFile(void)";
  QString file;
  file = QFileDialog::getSaveFileName(this,
                                      tr("Save Image"),NULL,tr("ImageFile(*.png *.jpg *.bmp)"));
  _area->savePicture(file);
  filename = file;
  qDebug()<<file;
}

void PaintWindow::quit(void)  {
  exit(0);
}


void PaintWindow::draw(void){
  _saveAct->setDisabled(false);
  _saveAsAct->setDisabled(false);
}

