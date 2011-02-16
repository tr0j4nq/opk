#ifndef INSTANCE_H
#define INSTANCE_H
#include <QPolygon>
#include <math.h>
#include <string>
#include "painter.h"
#define PI 3.14159265

using namespace std;

typedef struct{
    double l;
    int n;
}srodek;

class Instance
{
public:
    Instance(int,int,int,int,int,int,int);
    void generate();
private:
    int width,height,number,polygonsWidth,polygonsHeight,polygonsMaxV;
public:
    int polygonsNumber;
    QPolygon polygon;
    QPolygon wypukly;
    QVector<QPolygon> polygons;
    QVector<QPoint> srodki;
    QVector<QPolygon> otoczki;
    QPolygon otoczka;
    QVector<int> tabx;
    QVector<int> taby;
    QVector<QVector<double> > tab;
    double minimum;
    QVector<QVector<double> > drogi;
    bool inter;
    QVector<QVector<srodek> > heura;
    QVector<QVector<int> >poprzednik;
};

#endif // INSTANCE_H
