#include "csousfenetre.h"

Csousfenetre::Csousfenetre() : QWidget()
{

}

Csousfenetre::~Csousfenetre()
{

}

//CHARGEMENT DE L'IMAGE
void Csousfenetre::ouvrirImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open...",QString(),"Image (*.png *.jpg *.jpeg)");
    bool imageLoaded = m_image.load(fileName);

    if(imageLoaded==1) //pour savoir si l'image a bien été ouverte
    {
        QMessageBox msg;
        msg.setText("L'image a bien été ouverte");
        msg.exec();
    }

    if (imageLoaded) //pour addapter ma fenetre a la taille de mon image
    {
        setFixedSize(m_image.width(),m_image.height());
    }

    m_oldimage=m_image;

}

void Csousfenetre::paintEvent(QPaintEvent*event)
{
    QPainter painter(this);
    painter.drawImage(0,0,m_image);
}

void Csousfenetre::mousePressEvent(QMouseEvent*event)
{
   m_click++;
   //m_coord=event->pos();
   //qDebug()<<m_coord.x() << " " <<m_coord.y();
   if (event->button() == Qt::LeftButton){
        if (m_click==1){
            m_firstclick=event->pos();
            drawPoint();
            qDebug() << m_firstclick;
            return;
        }
        if (m_click==2){
            m_lastclick=event->pos();
            qDebug() << m_lastclick;
            drawLine();
            m_click=0;
            return;
        }
   }

   if (event->button() == Qt::RightButton){
       m_click=0;
       clearImage();
       return;
   }
}

void Csousfenetre::drawPoint(){
     QPainter contain(&m_image);

     QPainter stylo;
     stylo.setPen( QPen(Qt::blue, 100,Qt::SolidLine, Qt::RoundCap));
     contain.drawPoint(m_firstclick);
     update();

}


void Csousfenetre::drawLine(){

    QPainter ligne(&m_image);
    //QPen pen_ligne;

    ligne.setPen( QPen(Qt::black,3, Qt::SolidLine) );
    ligne.drawLine(m_firstclick,m_lastclick);
    QLineF line(m_firstclick,m_lastclick);

    distpixel = line.length();
    qDebug() << distpixel;

    update();
}


void Csousfenetre::clearImage(){
    m_image=m_oldimage;
    update();
}

double Csousfenetre::getDistPixel(){
    double dx = m_firstclick.x() - m_lastclick.x();
    double dy = m_firstclick.y() - m_lastclick.y();
    double dist = sqrt(dx*dx + dy*dy);
    return dist;

}
