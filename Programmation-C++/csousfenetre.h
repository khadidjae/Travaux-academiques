#ifndef CSOUSFENETRE_H
#define CSOUSFENETRE_H
#include <QWidget>
#include <QImage>
#include <QString>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QTransform>
#include <QPoint>
#include <QDebug>
#include <QLabel>
#include <QToolTip>
//#include <Qpen>

//Classe servant à charger l'image dans une sous fenetre qui sera disposé dans un Layout de
//ma fenêtre principal.

class Csousfenetre: public QWidget
{
Q_OBJECT

public:
    Csousfenetre();
    virtual ~Csousfenetre();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    double getDistPixel();

 private:
    QImage m_image;
    QImage m_oldimage;

   // QPoint m_coord;
    QPoint m_firstclick;
    QPoint m_lastclick;
    int m_click;
    float distpixel;

public slots:
    void ouvrirImage();
    void drawPoint();
    void drawLine();
    void clearImage();

};
#endif // CSOUSFENETRE_H
