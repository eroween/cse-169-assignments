/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "mainwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTest;
    QAction *actionTube;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_6;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *joint_name;
    QHBoxLayout *horizontalLayout;
    QLabel *limitx;
    QDoubleSpinBox *limitxmin;
    QDoubleSpinBox *limitxmax;
    QHBoxLayout *horizontalLayout_2;
    QLabel *limity;
    QDoubleSpinBox *limitymin;
    QDoubleSpinBox *limitymax;
    QHBoxLayout *horizontalLayout_5;
    QLabel *limitz;
    QDoubleSpinBox *limitzmin;
    QDoubleSpinBox *limitzmax;
    QHBoxLayout *horizontalLayout_4;
    QLabel *rotation;
    QDoubleSpinBox *rotationx;
    QDoubleSpinBox *rotationy;
    QDoubleSpinBox *rotationz;
    QHBoxLayout *horizontalLayout_3;
    QLabel *position;
    QDoubleSpinBox *positionx;
    QDoubleSpinBox *positiony;
    QDoubleSpinBox *positionz;
    MainWidget *openGLWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget;
    QWidget *Skeleton;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1154, 600);
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionTube = new QAction(MainWindow);
        actionTube->setObjectName(QStringLiteral("actionTube"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_6 = new QHBoxLayout(centralwidget);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(250, 0));
        widget->setMaximumSize(QSize(300, 16777215));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        joint_name = new QLabel(widget);
        joint_name->setObjectName(QStringLiteral("joint_name"));
        joint_name->setMinimumSize(QSize(0, 20));
        joint_name->setMaximumSize(QSize(16777215, 20));
        joint_name->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(joint_name, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        limitx = new QLabel(widget);
        limitx->setObjectName(QStringLiteral("limitx"));

        horizontalLayout->addWidget(limitx);

        limitxmin = new QDoubleSpinBox(widget);
        limitxmin->setObjectName(QStringLiteral("limitxmin"));
        limitxmin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        limitxmin->setMinimum(-100000);
        limitxmin->setMaximum(100000);

        horizontalLayout->addWidget(limitxmin);

        limitxmax = new QDoubleSpinBox(widget);
        limitxmax->setObjectName(QStringLiteral("limitxmax"));
        limitxmax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        limitxmax->setMinimum(-100000);
        limitxmax->setMaximum(100000);

        horizontalLayout->addWidget(limitxmax);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, -1, -1);
        limity = new QLabel(widget);
        limity->setObjectName(QStringLiteral("limity"));
        limity->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(limity);

        limitymin = new QDoubleSpinBox(widget);
        limitymin->setObjectName(QStringLiteral("limitymin"));
        limitymin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        limitymin->setMinimum(-1e+06);
        limitymin->setMaximum(1e+06);

        horizontalLayout_2->addWidget(limitymin);

        limitymax = new QDoubleSpinBox(widget);
        limitymax->setObjectName(QStringLiteral("limitymax"));
        limitymax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        limitymax->setMinimum(-1e+06);
        limitymax->setMaximum(1e+06);

        horizontalLayout_2->addWidget(limitymax);


        gridLayout_3->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        limitz = new QLabel(widget);
        limitz->setObjectName(QStringLiteral("limitz"));

        horizontalLayout_5->addWidget(limitz);

        limitzmin = new QDoubleSpinBox(widget);
        limitzmin->setObjectName(QStringLiteral("limitzmin"));
        limitzmin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        limitzmin->setMinimum(-1e+06);
        limitzmin->setMaximum(1e+06);

        horizontalLayout_5->addWidget(limitzmin);

        limitzmax = new QDoubleSpinBox(widget);
        limitzmax->setObjectName(QStringLiteral("limitzmax"));
        limitzmax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        limitzmax->setMinimum(-1e+06);
        limitzmax->setMaximum(1e+06);

        horizontalLayout_5->addWidget(limitzmax);


        gridLayout_3->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        rotation = new QLabel(widget);
        rotation->setObjectName(QStringLiteral("rotation"));

        horizontalLayout_4->addWidget(rotation);

        rotationx = new QDoubleSpinBox(widget);
        rotationx->setObjectName(QStringLiteral("rotationx"));
        rotationx->setCursor(QCursor(Qt::ArrowCursor));
        rotationx->setMouseTracking(false);
        rotationx->setFocusPolicy(Qt::WheelFocus);
        rotationx->setButtonSymbols(QAbstractSpinBox::NoButtons);
        rotationx->setAccelerated(true);
        rotationx->setMinimum(-1e+06);
        rotationx->setMaximum(1e+06);

        horizontalLayout_4->addWidget(rotationx);

        rotationy = new QDoubleSpinBox(widget);
        rotationy->setObjectName(QStringLiteral("rotationy"));
        rotationy->setButtonSymbols(QAbstractSpinBox::NoButtons);
        rotationy->setMinimum(-1e+06);
        rotationy->setMaximum(1e+06);

        horizontalLayout_4->addWidget(rotationy);

        rotationz = new QDoubleSpinBox(widget);
        rotationz->setObjectName(QStringLiteral("rotationz"));
        rotationz->setButtonSymbols(QAbstractSpinBox::NoButtons);
        rotationz->setMinimum(-1e+06);
        rotationz->setMaximum(1e+06);

        horizontalLayout_4->addWidget(rotationz);


        gridLayout_3->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        position = new QLabel(widget);
        position->setObjectName(QStringLiteral("position"));

        horizontalLayout_3->addWidget(position);

        positionx = new QDoubleSpinBox(widget);
        positionx->setObjectName(QStringLiteral("positionx"));
        positionx->setButtonSymbols(QAbstractSpinBox::NoButtons);
        positionx->setMinimum(-1e+06);
        positionx->setMaximum(1e+06);

        horizontalLayout_3->addWidget(positionx);

        positiony = new QDoubleSpinBox(widget);
        positiony->setObjectName(QStringLiteral("positiony"));
        positiony->setButtonSymbols(QAbstractSpinBox::NoButtons);
        positiony->setMinimum(-1e+06);
        positiony->setMaximum(1e+06);

        horizontalLayout_3->addWidget(positiony);

        positionz = new QDoubleSpinBox(widget);
        positionz->setObjectName(QStringLiteral("positionz"));
        positionz->setButtonSymbols(QAbstractSpinBox::NoButtons);
        positionz->setMinimum(-1e+06);
        positionz->setMaximum(1e+06);

        horizontalLayout_3->addWidget(positionz);


        gridLayout_3->addLayout(horizontalLayout_3, 5, 0, 1, 1);


        horizontalLayout_6->addWidget(widget);

        openGLWidget = new MainWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setMinimumSize(QSize(600, 400));

        horizontalLayout_6->addWidget(openGLWidget);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(250, 0));
        tabWidget->setMaximumSize(QSize(300, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tab->setMinimumSize(QSize(270, 0));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        treeWidget = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMinimumSize(QSize(250, 0));

        gridLayout_2->addWidget(treeWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        Skeleton = new QWidget();
        Skeleton->setObjectName(QStringLiteral("Skeleton"));
        Skeleton->setMinimumSize(QSize(250, 0));
        gridLayout = new QGridLayout(Skeleton);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeWidget_2 = new QTreeWidget(Skeleton);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem1);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));
        treeWidget_2->setMinimumSize(QSize(250, 0));

        gridLayout->addWidget(treeWidget_2, 0, 0, 1, 1);

        tabWidget->addTab(Skeleton, QString());

        horizontalLayout_6->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1154, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionTest);
        toolBar->addAction(actionTube);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionTest->setText(QApplication::translate("MainWindow", "wasp", 0));
        actionTube->setText(QApplication::translate("MainWindow", "tube", 0));
        joint_name->setText(QApplication::translate("MainWindow", "Name", 0));
        limitx->setText(QApplication::translate("MainWindow", "limit_x", 0));
        limity->setText(QApplication::translate("MainWindow", "limit_y", 0));
        limitz->setText(QApplication::translate("MainWindow", "limit_z", 0));
        rotation->setText(QApplication::translate("MainWindow", "rotation", 0));
        position->setText(QApplication::translate("MainWindow", "position", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "SceneGraph", 0));
        tabWidget->setTabText(tabWidget->indexOf(Skeleton), QApplication::translate("MainWindow", "Skeleton", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
