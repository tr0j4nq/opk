#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "painter.h"
#include <time.h>
#include <stdio.h>
#include "instance.h"
#include "solve.h"
#include <windows.h>
#include <sstream>
#include <QString>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
public slots:
    void generateInst();
    void solveInst();
    void przerwij();
    void zapisuj();
private:
    Painter* painter;
    QLineEdit* widthEdit;
    QLineEdit* heightEdit;
    QLineEdit* numberEdit;
    QLineEdit* polygonsEdit;
    QLineEdit* polygonsWidthEdit;
    QLineEdit* polygonsHeightEdit;
    QLineEdit* polygonsMaxVEdit;
    QLineEdit* timer;
    QPushButton* generateButton;
    QPushButton* solveButton;
    QPushButton* przerwijButton;
    QPushButton* zapisz;
    QLabel* widthLabel;
    QLabel* heightLabel;
    QLabel* numberLabel;
    QLabel* polygonsNumberLabel;
    QLabel* polygonsWidthLabel;
    QLabel* polygonsHeightLabel;
    QLabel* polygonsMaxVLabel;
    Instance* instance;
    Solve* solve;
    QString czas;
};

#endif // MAINWINDOW_H
