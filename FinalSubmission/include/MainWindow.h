//----------------------------------------------------------------------------------------------------------------------
/// @file MainWindow.h
/// @class MainWindow
/// @brief this class connects GUI with NGLScene
//----------------------------------------------------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <NGLScene.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *m_ui;
  NGLScene *m_gl;
  bool m_update;


private slots :
 void newSwarmPressed();
 void addSingleBoid();

};

#endif // MAINWINDOW_H
