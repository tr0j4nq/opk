#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QtGui>
#include "instance.h"

class Instance;

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = 0);
    void drawInstance(Instance* instance);
    void drawSolve(Instance* instance);

signals:

public slots:

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
};

#endif // PAINTER_H
