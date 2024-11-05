#include <QtWidgets>
#include <QSlider>
#include "cfenetre.h"
#include <QApplication>
#include <QPushButton>

int main (int argc,char*argv[])
{
    QApplication app(argc,argv);

    CFenetre fenetre;
    fenetre.show();

    return app.exec();

}
