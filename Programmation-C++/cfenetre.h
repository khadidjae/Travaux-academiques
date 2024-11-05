#ifndef CFENETRE_H
#define CFENETRE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QAbstractButton>
#include <QApplication>

#include <qobject.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QGroupBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QComboBox>

#include <QFileDialog>
#include <QDebug>

#include <QLabel>
#include <QLineEdit>
#include <cmath>
#include <QGridLayout>
#include <QPicture>
#include <QPixmap>

#include "csousfenetre.h"
#include "ccalculateur.h"


class CFenetre: public QWidget{

Q_OBJECT

public:
    CFenetre();
    virtual~CFenetre();

private:
    QPushButton* m_bouton;
    Csousfenetre* m_ecgfenetre;
    QPushButton* m_fcbutton;

    CCalcul* m_calculateur;
    double m_scalefactor;
    double m_frequence;


    // ORGANISATION DES ÉLÉMENTS
    QVBoxLayout* m_menulayout;
    QHBoxLayout* m_ecglayout;

    // Widget Echelle
    QGroupBox* m_groupbox;
    QDoubleSpinBox* m_timebox;
    QComboBox* m_unitebox;

    QLabel* labeltemps;
    QLabel* labelunite;
    QString unite;

    QGridLayout* m_gridlayout;
    double distechelle;

    QPushButton* m_boutonok;
    QPushButton* m_boutonaide;

    QGroupBox* m_fcgroupbox;
    QGridLayout* m_fclayout;
    QLabel* m_fclabel;
    QLabel* m_label;

    QLabel *instructionlabel;
    QLabel* imagetuto;
    QPixmap pixmap;



public slots :
    void setscale();
    void affichefc();
    void echelledispo();
    void scalehelp();
};

#endif // CFENETRE_H
