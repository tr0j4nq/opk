#ifndef SOLVE_H
#define SOLVE_H
#include <QPolygon>
#include "instance.h"
#include <stdlib.h>
#include <math.h>
#include <QStack>
#include <QMessageBox>
#include <iterator>
#include "painter.h"
#include <QCheckBox>

class Solve
{
public:
    Solve();
    void otoczka(Instance*,Painter*);
};

#endif // SOLVE_H
