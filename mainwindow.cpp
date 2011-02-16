#include "mainwindow.h"
#include <fstream>
#include <string>
#include <signal.h>

using namespace std;

MainWindow::MainWindow()
{
    srand(time(NULL));

    setWindowTitle("Optymalizacja Kombinatoryczna");

    generateButton = new QPushButton("Generuj",this);
    generateButton->show();

    przerwijButton = new QPushButton("Przerwij",this);
    zapisz = new QPushButton("Zapisz",this);
    zapisz->show();


    painter = new Painter(this);
    painter->show();

    widthEdit = new QLineEdit;
    widthEdit->setMaximumWidth(100);
    widthEdit->setMinimumWidth(100);
    widthEdit->setText("850");
    heightEdit = new QLineEdit;
    heightEdit->setMaximumWidth(100);
    heightEdit->setMinimumWidth(100);
    heightEdit->setText("500");
    numberEdit = new QLineEdit;
    numberEdit->setMaximumWidth(100);
    numberEdit->setMinimumWidth(100);
    numberEdit->setText("10");

    QGridLayout* mainLayout = new QGridLayout;
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    QHBoxLayout* button2Layout = new QHBoxLayout;

    widthLabel = new QLabel;
    widthLabel->setMinimumWidth(70);
    widthLabel->setMaximumWidth(70);
    widthLabel->setText("Szerokosc");
    heightLabel = new QLabel;
    heightLabel->setMinimumWidth(80);
    heightLabel->setMaximumWidth(80);
    heightLabel->setText("Wysokosc");
    numberLabel = new QLabel;
    numberLabel->setMinimumWidth(80);
    numberLabel->setMaximumWidth(80);
    numberLabel->setText("Liczba wierzcholkow");
    timer = new QLineEdit;
    timer->setText("0");
    timer->setReadOnly(true);

    buttonLayout->addWidget(generateButton);
    buttonLayout->addWidget(widthLabel);
    buttonLayout->addWidget(widthEdit);
    buttonLayout->addWidget(heightLabel);
    buttonLayout->addWidget(heightEdit);
    buttonLayout->addWidget(numberLabel);
    buttonLayout->addWidget(numberEdit);
    buttonLayout->addStretch();
    buttonLayout->addWidget(przerwijButton);
    buttonLayout->addWidget(timer);


    solveButton = new QPushButton("Rozwiaz",this);
    solveButton->show();
    solveButton->setEnabled(0);
    polygonsNumberLabel = new QLabel;
    polygonsNumberLabel->setMinimumWidth(70);
    polygonsNumberLabel->setMaximumWidth(70);
    polygonsNumberLabel->setText("Liczba dziur");
    polygonsEdit = new QLineEdit;
    polygonsEdit->setMaximumWidth(100);
    polygonsEdit->setMinimumWidth(100);
    polygonsEdit->setText("2");
    polygonsWidthLabel = new QLabel;
    polygonsWidthLabel->setMinimumWidth(80);
    polygonsWidthLabel->setMaximumWidth(80);
    polygonsWidthLabel->setText("Maks. szerokosc");
    polygonsHeightLabel = new QLabel;
    polygonsHeightLabel->setMinimumWidth(80);
    polygonsHeightLabel->setMaximumWidth(80);
    polygonsHeightLabel->setText("Maks. wysokosc");
    polygonsWidthEdit = new QLineEdit;
    polygonsWidthEdit->setMaximumWidth(100);
    polygonsWidthEdit->setMinimumWidth(100);
    polygonsWidthEdit->setText("100");
    polygonsHeightEdit = new QLineEdit;
    polygonsHeightEdit->setMaximumWidth(100);
    polygonsHeightEdit->setMinimumWidth(100);
    polygonsHeightEdit->setText("100");
    polygonsMaxVLabel = new QLabel;
    polygonsMaxVLabel->setMinimumWidth(130);
    polygonsMaxVLabel->setMaximumWidth(130);
    polygonsMaxVLabel->setText("Maks. liczba wierzcholkow");
    polygonsMaxVEdit = new QLineEdit;
    polygonsMaxVEdit->setMaximumWidth(100);
    polygonsMaxVEdit->setMinimumWidth(100);
    polygonsMaxVEdit->setText("5");

    button2Layout->addWidget(solveButton);
    button2Layout->addWidget(polygonsNumberLabel);
    button2Layout->addWidget(polygonsEdit);
    button2Layout->addWidget(polygonsWidthLabel);
    button2Layout->addWidget(polygonsWidthEdit);
    button2Layout->addWidget(polygonsHeightLabel);
    button2Layout->addWidget(polygonsHeightEdit);
    button2Layout->addWidget(polygonsMaxVLabel);
    button2Layout->addWidget(polygonsMaxVEdit);
    button2Layout->addStretch();
    button2Layout->addWidget(zapisz);

    mainLayout->addLayout(buttonLayout, 0, 0);
    mainLayout->addLayout(button2Layout,1,0);
    mainLayout->addWidget(painter, 2, 0);

    setLayout(mainLayout);

    connect(generateButton, SIGNAL(clicked()), this, SLOT(generateInst()));
    connect(solveButton, SIGNAL(clicked()), this, SLOT(solveInst()));
    connect(przerwijButton,SIGNAL(clicked()),this,SLOT(przerwij()));
    connect(zapisz,SIGNAL(clicked()),this,SLOT(zapisuj()));

    showMaximized();
}

void MainWindow::zapisuj(){
    string plikN="wynik2.txt";
    ofstream plik;
    remove(plikN.c_str());
    plik.open(plikN.c_str(),fstream::app);
    for(int i=3;i<=15;i+=3){
        stringstream ss1;
        ss1<<i;
        QString str1;
        str1=str1.fromStdString(ss1.str());
        numberEdit->setText(str1);
        for(int j=3;j<=15;j+=3){
            stringstream ss2;
            ss2<<j;
            QString str2;
            str2=str2.fromStdString(ss2.str());
            polygonsMaxVEdit->setText(str2);
            for(int k=1;k<=25;k++){
                stringstream ss3;
                ss3<<k;
                QString str3;
                str3=str3.fromStdString(ss3.str());
                polygonsEdit->setText(str3);
                for(int l=0;l<10;l++){
                    try{
                    generateInst();
                    solveInst();
                    plik<<"liczba_wierzcholkow_figury: "<<i<<" maks_liczba_wierzcholkow_dziur: "<<j<<" ilosc_dziur: "<<k<<" czas: "<<this->czas.toStdString()<<endl;
                    }
                    catch(char *)
                    {
                    //niech przejdzie do kolejnej instancji po prostu
                    }
                    catch(...)
                    {
                    l--;
                    }
                }
            }
        }
    }
    plik.close();
}

void MainWindow::przerwij(){
    instance->inter=true;
    generateButton->setEnabled(1);
}

void MainWindow::solveInst(){
    instance->inter=false;
    solveButton->setEnabled(0);
    generateButton->setEnabled(0);
    timer->setText("0");
    LARGE_INTEGER Freq;
    LARGE_INTEGER TimeEnd;
    LARGE_INTEGER TimeDiff;
    LARGE_INTEGER TimeStart;
    QueryPerformanceFrequency(&Freq);
    solve = new Solve();
    QueryPerformanceCounter(&TimeStart);
    solve->otoczka(instance,painter);
    QueryPerformanceCounter(&TimeEnd);
    TimeDiff.QuadPart=(TimeEnd.QuadPart*1000-TimeStart.QuadPart*1000)/Freq.QuadPart;
    stringstream ss;
    ss<<TimeDiff.QuadPart;
    QString str;
    str=str.fromStdString(ss.str());
    timer->setText(str);
    this->czas=str;
    generateButton->setEnabled(1);
    delete instance;
}

void MainWindow::generateInst()
{
    generateButton->setEnabled(0);
    solveButton->setEnabled(0);
    instance =new Instance(numberEdit->text().toInt(),widthEdit->text().toInt(),heightEdit->text().toInt(),polygonsEdit->text().toInt(),polygonsWidthEdit->text().toInt(),polygonsHeightEdit->text().toInt(),polygonsMaxVEdit->text().toInt());
    instance->inter=false;
    instance->generate();
    if(!instance->inter){
        painter->drawInstance(instance);
        solveButton->setEnabled(1);
    }
    generateButton->setEnabled(1);
}
