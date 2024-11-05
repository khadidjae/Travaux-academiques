#include "ccalculateur.h"
CCalcul::CCalcul()
{

}

CCalcul::~CCalcul()
{

}

double CCalcul::calculatescale(double time, QString unit, Csousfenetre* sousfenetre)
{
double distPixel = sousfenetre->getDistPixel();

//Convertion du temps en seconde selon l'unité sélectionné
double timeSec=0;

    if (unit == "s") {
           timeSec = time;
    } else if (unit == "ms") {
           timeSec = time / 1000.0;
    } else if (unit == "us") {
           timeSec = time / 1000000.0;
    }

    // Calcul distance pixel en temps
    double m_scalingFactor = distPixel / timeSec;
    return m_scalingFactor;
}
