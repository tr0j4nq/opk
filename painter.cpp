#include "painter.h"
#include <QtGui>

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene,this);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}   

void Painter::drawInstance(Instance* instance){
    view->setRenderHints(QPainter::Antialiasing);
    scene->clear();
    scene->addPolygon(instance->polygon,QPen(QBrush(QColor(0,180,0)), 1),QBrush(QColor(0,180,0)));
    for(int i=0;i<instance->polygonsNumber;i++)
        scene->addPolygon(instance->polygons[i],QPen(QBrush(QColor(255,255,255)), 1),QBrush(QColor(255,255,255)));

}

void Painter::drawSolve(Instance* instance){
    view->setRenderHints(QPainter::Antialiasing);
    scene->clear();
    scene->addPolygon(instance->polygon,QPen(QBrush(QColor(0,180,0)), 1),QBrush(QColor(0,180,0)));
    for(int i=0;i<instance->polygonsNumber;i++)
        scene->addPolygon(instance->polygons[i],QPen(QBrush(QColor(255,255,255)), 1),QBrush(QColor(255,255,255)));
    scene->addPolygon(instance->otoczka,QPen(QBrush(QColor(50,50,50)), 1));
}

