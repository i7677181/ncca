/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *m_add;
    QSlider *m_cohesion;
    QSlider *m_alignment;
    QSlider *m_separation;
    QSlider *m_mass;
    QSlider *m_speed;
    QWidget *gridLayoutWidget;
    QGridLayout *m_grid;
    QSpinBox *m_swarmCount;
    QPushButton *m_newSwarm;
    QLabel *cohesion_label;
    QLabel *alignment_label;
    QLabel *separation_label;
    QLabel *mass_label;
    QLabel *speed_label;
    QLabel *label;
    QPushButton *m_remove;
    QSlider *m_sepDist;
    QLabel *label_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1082, 666);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        m_add = new QPushButton(centralwidget);
        m_add->setObjectName(QStringLiteral("m_add"));
        m_add->setGeometry(QRect(610, 470, 141, 91));
        m_cohesion = new QSlider(centralwidget);
        m_cohesion->setObjectName(QStringLiteral("m_cohesion"));
        m_cohesion->setGeometry(QRect(610, 170, 160, 16));
        m_cohesion->setOrientation(Qt::Horizontal);
        m_alignment = new QSlider(centralwidget);
        m_alignment->setObjectName(QStringLiteral("m_alignment"));
        m_alignment->setGeometry(QRect(610, 210, 160, 16));
        m_alignment->setOrientation(Qt::Horizontal);
        m_separation = new QSlider(centralwidget);
        m_separation->setObjectName(QStringLiteral("m_separation"));
        m_separation->setGeometry(QRect(610, 250, 160, 16));
        m_separation->setOrientation(Qt::Horizontal);
        m_mass = new QSlider(centralwidget);
        m_mass->setObjectName(QStringLiteral("m_mass"));
        m_mass->setGeometry(QRect(610, 340, 160, 16));
        m_mass->setOrientation(Qt::Horizontal);
        m_speed = new QSlider(centralwidget);
        m_speed->setObjectName(QStringLiteral("m_speed"));
        m_speed->setGeometry(QRect(610, 380, 160, 16));
        m_speed->setOrientation(Qt::Horizontal);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 571, 531));
        m_grid = new QGridLayout(gridLayoutWidget);
        m_grid->setObjectName(QStringLiteral("m_grid"));
        m_grid->setContentsMargins(0, 0, 0, 0);
        m_swarmCount = new QSpinBox(centralwidget);
        m_swarmCount->setObjectName(QStringLiteral("m_swarmCount"));
        m_swarmCount->setGeometry(QRect(700, 80, 71, 51));
        m_swarmCount->setMaximum(2000);
        m_newSwarm = new QPushButton(centralwidget);
        m_newSwarm->setObjectName(QStringLiteral("m_newSwarm"));
        m_newSwarm->setGeometry(QRect(780, 50, 131, 81));
        m_newSwarm->setMinimumSize(QSize(111, 51));
        cohesion_label = new QLabel(centralwidget);
        cohesion_label->setObjectName(QStringLiteral("cohesion_label"));
        cohesion_label->setGeometry(QRect(790, 170, 121, 21));
        alignment_label = new QLabel(centralwidget);
        alignment_label->setObjectName(QStringLiteral("alignment_label"));
        alignment_label->setGeometry(QRect(780, 210, 131, 21));
        separation_label = new QLabel(centralwidget);
        separation_label->setObjectName(QStringLiteral("separation_label"));
        separation_label->setGeometry(QRect(790, 240, 141, 31));
        mass_label = new QLabel(centralwidget);
        mass_label->setObjectName(QStringLiteral("mass_label"));
        mass_label->setGeometry(QRect(790, 320, 261, 51));
        speed_label = new QLabel(centralwidget);
        speed_label->setObjectName(QStringLiteral("speed_label"));
        speed_label->setGeometry(QRect(790, 360, 201, 61));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(590, 60, 81, 71));
        m_remove = new QPushButton(centralwidget);
        m_remove->setObjectName(QStringLiteral("m_remove"));
        m_remove->setGeometry(QRect(790, 470, 131, 91));
        m_sepDist = new QSlider(centralwidget);
        m_sepDist->setObjectName(QStringLiteral("m_sepDist"));
        m_sepDist->setGeometry(QRect(610, 290, 160, 16));
        m_sepDist->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(780, 270, 171, 41));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        m_add->setText(QApplication::translate("MainWindow", "Add Boid", 0));
        m_newSwarm->setText(QApplication::translate("MainWindow", "Spawn!", 0));
        cohesion_label->setText(QApplication::translate("MainWindow", "Cohesion", 0));
        alignment_label->setText(QApplication::translate("MainWindow", "Alignment", 0));
        separation_label->setText(QApplication::translate("MainWindow", "Separation", 0));
        mass_label->setText(QApplication::translate("MainWindow", "Mass/Resistance", 0));
        speed_label->setText(QApplication::translate("MainWindow", "Speed/Drive", 0));
        label->setText(QApplication::translate("MainWindow", "Count:", 0));
        m_remove->setText(QApplication::translate("MainWindow", "  Remove Boid", 0));
        label_2->setText(QApplication::translate("MainWindow", "Separation Distance", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
