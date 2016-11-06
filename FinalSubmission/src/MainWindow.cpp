#include "include/MainWindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>


MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), m_ui(new Ui::MainWindow)
{

  m_ui->setupUi(this);
  QGLFormat format;
  format.setVersion(4,1);
  format.setProfile( QGLFormat::CoreProfile);
  m_gl=new NGLScene(this);
  m_ui->m_grid->addWidget(m_gl,0,0,2,1);
  m_update=false;

  connect(m_ui->m_add,SIGNAL(pressed()),this,SLOT(addSingleBoid()));
  connect(m_ui->m_remove,SIGNAL(pressed()),m_gl,SLOT(removeBoid()));
  connect(m_ui->m_newSwarm,SIGNAL(pressed()),this,SLOT(newSwarmPressed()));
  connect(m_ui->m_cohesion,SIGNAL(sliderMoved(int)),m_gl,SLOT(setCohesion(int)));
  connect(m_ui->m_separation,SIGNAL(sliderMoved(int)),m_gl,SLOT(setSeparation(int)));
  connect(m_ui->m_alignment,SIGNAL(sliderMoved(int)),m_gl,SLOT(setAlignment(int)));
  connect(m_ui->m_speed,SIGNAL(sliderMoved(int)),m_gl,SLOT(setSpeed(int)));
  connect(m_ui->m_mass,SIGNAL(sliderMoved(int)),m_gl,SLOT(setMass(int)));
  connect(m_ui->m_sepDist,SIGNAL(sliderMoved(int)),m_gl,SLOT(setSepDist(int)));

}

MainWindow::~MainWindow()
{
  delete m_ui;
}

void MainWindow::newSwarmPressed()
{
  m_gl->newSwarm(m_ui->m_swarmCount->value(),
                 m_ui->m_cohesion->value(),
                 m_ui->m_separation->value(),
                 m_ui->m_alignment->value(),
                 (m_ui->m_speed->value()/10.0),
                 m_ui->m_mass->value());
}

void MainWindow::addSingleBoid()
{
  m_gl->createSwarm(m_ui->m_cohesion->value(),
                m_ui->m_separation->value(),
                m_ui->m_alignment->value(),
                (m_ui->m_speed->value()/10.0),
                m_ui->m_mass->value());
}


