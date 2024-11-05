#ifndef CCALCULATEUR_H
#define CCALCULATEUR_H

#include <QPoint>
#include "csousfenetre.h"

class CCalcul
{
public:
    CCalcul();
    virtual~CCalcul();

private:

public slots:
    double calculatescale(double time, QString unit, Csousfenetre* sousfenetre);
};

#endif // CCALCULATEUR_H
